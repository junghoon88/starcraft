#include "stdafx.h"
#include "gameController.h"
#include "player.h"

#include <functional>


gameController::gameController()
	: _imgInterface(NULL), _imgCursor(NULL), _hotkeys(NULL), _miniMap(NULL), _myPlayer(NULL), _gameMap(NULL)
{
	_cursorState = CURSORSTATE_IDLE;

	_curCommand = COMMAND_NONE;

	ZeroMemory(&_unitCommandInfo,	sizeof(tagUnitCommands));

	ZeroMemory(&_commandSet,		sizeof(tagCommandSet) * COMMAND_MAX);



	ZeroMemory(&_selectInfo, sizeof(tagSelectInfo));


	_cursorPt = { 0, 0 };
	_cursorTile = { 0, 0 };


}


gameController::~gameController()
{
	SAFE_RELEASEDELETE(_hotkeys);
	SAFE_RELEASEDELETE(_miniMap);

	for (int i = 0; i < COMMAND_MAX; i++)
	{
		SAFE_RELEASEDELETE(_commandSet[i].button);
	}
}

HRESULT gameController::init(PLAYER playerNum, RACES races)
{
	_playerNum = playerNum;

	switch (races)
	{
	case RACES_TERRAN:
		_imgInterface = IMAGEMANAGER->findImage(L"interfaceT");
		break;
	case RACES_PROTOSS:
		_imgInterface = IMAGEMANAGER->findImage(L"interfaceP");
		break;
	case RACES_ZERG:
		_imgInterface = IMAGEMANAGER->findImage(L"interfaceZ");
		break;
	}

	initCommandSet();

	_miniMap = new miniMap;
	_miniMap->init();

	_hotkeys = new hotkeys;
	_hotkeys->init();


	//debug
	_isInInterface = false;
	_isClicked = false;
	_isDraging = false;
	_findTarget = false;
	_findLocation = false;
	_buildingSize = { 0, 0 };
	ZeroMemory(&_buildingPlaceable, sizeof(BUILDSTATE) * OBJECTSIZE_MAX_X * OBJECTSIZE_MAX_Y);
	_buildable = false;

	return S_OK;
}

void gameController::release(void)
{

}

void gameController::update(void)
{
	calcMouseRealPosition();

	//키보드입력 먼저 확인하고
	if (actionHotkeys() == FALSE)
	{
		//키보드입력이 없을 경우
		COLORREF color = GetPixel(_imgInterface->getMemDC(), _ptMouse.x, _ptMouse.y) & 0x00FFFFFF;

		if (color == RGB(255, 0, 255))
		{
			//인터페이스 영역 밖에 마우스가 있을경우
			_isInInterface = false;
			actionMouseMap();
		}
		else
		{
			//인터페이스 영역 안에 마우스가 있을경우
			_isInInterface = true;

			//minimap
			RECT rcMinimap = _miniMap->getRect();
			if (PtInRect(&rcMinimap, _ptMouse))
			{
				actionMouseMiniMap();
			}

			//face
			//actionMouseImageFace();

			//command
			for (int i = 0; i < COMMAND_MAX; i++)
			{
				//버튼이 클릭되면 actionMouseCommandSet 함수를 호출한다.
				_commandSet[i].button->update();
			}
		}
	}

	actionCommand();
	setCommandSet();
	setImageCursor();
}

void gameController::render(void)
{

	if(_isDraging)
	{
		RECT rc = { _ptDragStart.x, _ptDragStart.y, _ptMouse.x, _ptMouse.y };
		RENDERMANAGER->insertLineRectangle(ZORDER_GAMEMOUSEDRAG, rc, PENVERSION_MOUSEDRAG);
	}

	renderBuildImage();

	renderInterface();

	renderCursor();
}

void gameController::initCommandSet(void)
{
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		int idx = i % 3;
		int idy = i / 3;

		_commandSet[i].rc = RectMake(506 + idx * 46, 358 + idy * 40, COMMAND_WIDTH, COMMAND_HEIGHT);
		_commandSet[i].button = new button;
	}
	

	_commandSet[0].button->init(L"", _commandSet[0].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc0, this);
	_commandSet[1].button->init(L"", _commandSet[1].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc1, this);
	_commandSet[2].button->init(L"", _commandSet[2].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc2, this);
	_commandSet[3].button->init(L"", _commandSet[3].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc3, this);
	_commandSet[4].button->init(L"", _commandSet[4].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc4, this);
	_commandSet[5].button->init(L"", _commandSet[5].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc5, this);
	_commandSet[6].button->init(L"", _commandSet[6].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc6, this);
	_commandSet[7].button->init(L"", _commandSet[7].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc7, this);
	_commandSet[8].button->init(L"", _commandSet[8].rc, {0,0}, {1,0}, {2,0}, &cbCommandFunc8, this);


	_commandSetEsc[0] = COMMAND_NONE;
	_commandSetEsc[1] = COMMAND_NONE;
	_commandSetEsc[2] = COMMAND_NONE;
	_commandSetEsc[3] = COMMAND_NONE;
	_commandSetEsc[4] = COMMAND_NONE;
	_commandSetEsc[5] = COMMAND_NONE;
	_commandSetEsc[6] = COMMAND_NONE;
	_commandSetEsc[7] = COMMAND_NONE;
	_commandSetEsc[8] = COMMAND_ESC;

	_commandSetBuild1[0] = COMMAND_BUILD_HATCHERY;			
	_commandSetBuild1[1] = COMMAND_BUILD_CREEPCOLONY;		
	_commandSetBuild1[2] = COMMAND_BUILD_EXTRACTOR;			
	_commandSetBuild1[3] = COMMAND_BUILD_SPAWNINGPOOL;		
	_commandSetBuild1[4] = COMMAND_BUILD_EVOLUTIONCHAMBER;	
	_commandSetBuild1[5] = COMMAND_NONE;					
	_commandSetBuild1[6] = COMMAND_BUILD_HYDRALISKDEN;		
	_commandSetBuild1[7] = COMMAND_NONE;					
	_commandSetBuild1[8] = COMMAND_ESC;						

	_commandSetBuild2[0] = COMMAND_BUILD_SPIRE;				
	_commandSetBuild2[1] = COMMAND_BUILD_QUEENSNEST;		
	_commandSetBuild2[2] = COMMAND_BUILD_NYDUSCANAL;		
	_commandSetBuild2[3] = COMMAND_BUILD_ULTRALISKCAVERN;	
	_commandSetBuild2[4] = COMMAND_BUILD_DEFILERMOUND;		
	_commandSetBuild2[5] = COMMAND_NONE;					
	_commandSetBuild2[6] = COMMAND_NONE;					
	_commandSetBuild2[7] = COMMAND_NONE;					
	_commandSetBuild2[8] = COMMAND_ESC;						

	_commandSetUnit[0] = COMMAND_NONE;
	_commandSetUnit[1] = COMMAND_NONE;
	_commandSetUnit[2] = COMMAND_NONE;
	_commandSetUnit[3] = COMMAND_NONE;
	_commandSetUnit[4] = COMMAND_NONE;
	_commandSetUnit[5] = COMMAND_NONE;
	_commandSetUnit[6] = COMMAND_NONE;
	_commandSetUnit[7] = COMMAND_NONE;
	_commandSetUnit[8] = COMMAND_NONE;
}


void gameController::actionMouseMap(void)
{
	POINT ptMouseReal;
	ptMouseReal.x = _ptMouse.x + MAINCAMERA->getCameraX();
	ptMouseReal.y = _ptMouse.y + MAINCAMERA->getCameraY();

	switch (_cursorState)
	{
	case CURSORSTATE_IDLE:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isClicked = true;
			_ptDragStart = _ptMouse;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (_isClicked)
			{
				//위치가 달라지면 드래그상태로 바꾼다.
				if (_ptDragStart.x != _ptMouse.x || _ptDragStart.y != _ptMouse.y)
				{
					_isDraging = true;
					_cursorState = CURSORSTATE_DRAGING;
				}
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_isClicked = false;

			if (_selectInfo.isSelected)
			{
				gameObject* target = getTargetInfo();

				if (target == NULL)
				{
					for (int i = 0; i < SELECTUNIT_MAX; i++)
					{
						if (_selectInfo.object[i] == NULL) continue;

						if (_selectInfo.object[i]->getIsBuilding())
						{
							_selectInfo.object[i]->receiveCommand(COMMAND_SETRALLYPOINT, ptMouseReal);
						}
						else
						{
							_selectInfo.object[i]->receiveCommand(COMMAND_MOVE, ptMouseReal);
						}
					}
				}
				else
				{
					for (int i = 0; i < SELECTUNIT_MAX; i++)
					{
						if (_selectInfo.object[i] == NULL) continue;

						if (_selectInfo.object[i]->getIsBuilding())
						{
							_selectInfo.object[i]->receiveCommand(COMMAND_SETRALLYPOINT, ptMouseReal);
						}
						else
						{
							if(target->getPlayerNum() == _playerNum)
							{
								_selectInfo.object[i]->receiveCommand(COMMAND_MOVE, target);
							}
							else
							{
								_selectInfo.object[i]->receiveCommand(COMMAND_ATTACK, target);
							}
						}
					}
				}
			}
		}
		else
		{
			_isClicked = false;

			TEAM team = searchObject();

			if (_findTarget)
			{
				switch (team)
				{
				case TEAM_NONE:			_cursorState = CURSORSTATE_FOCUS_TO_NEUTRAL;	break;
				case TEAM_NEUTRAL:		_cursorState = CURSORSTATE_FOCUS_TO_NEUTRAL;	break;
				case TEAM_MYTEAM:		_cursorState = CURSORSTATE_FOCUS_TO_ME;			break;
				case TEAM_FRIEND:		_cursorState = CURSORSTATE_FOCUS_TO_NEUTRAL;	break;
				case TEAM_ENEMY:		_cursorState = CURSORSTATE_FOCUS_TO_ENEMY;		break;
				}
			}
			else if (_findLocation)
			{
				if (_curCommand == COMMAND_BUILD_HATCHERY)
				{
					_cursorState = CURSORSTATE_BUILD_HATCHERY;
				}
				else if (_curCommand == COMMAND_BUILD_EXTRACTOR)
				{
					_cursorState = CURSORSTATE_BUILD_EXTRACTOR;
				}
				else
				{
					_cursorState = CURSORSTATE_BUILD_NORMAL;
				}
			}
			else
			{
				switch (team)
				{
				case TEAM_NONE:			_cursorState = CURSORSTATE_IDLE;			break;
				case TEAM_NEUTRAL:		_cursorState = CURSORSTATE_ON_NEUTRAL;		break;
				case TEAM_MYTEAM:		_cursorState = CURSORSTATE_ON_ME;			break;
				case TEAM_FRIEND:		_cursorState = CURSORSTATE_ON_NEUTRAL;		break;
				case TEAM_ENEMY:		_cursorState = CURSORSTATE_ON_ENEMY;		break;
				}
			}
		}
		break;
	case CURSORSTATE_FOCUS_TO_ME:
	case CURSORSTATE_FOCUS_TO_NEUTRAL:
	case CURSORSTATE_FOCUS_TO_ENEMY:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			gameObject* target = getTargetInfo();
			Unit* targetUnit = NULL;
			Building* targetBuilding = NULL;

			if (target == NULL)
			{
				for (int i = 0; i < SELECTUNIT_MAX; i++)
				{
					if (_selectInfo.object[i] == NULL) continue;

					_selectInfo.object[i]->receiveCommand(_curCommand, ptMouseReal);
				}
			}
			else
			{
				for (int i = 0; i < SELECTUNIT_MAX; i++)
				{
					if (_selectInfo.object[i] == NULL) continue;

					_selectInfo.object[i]->receiveCommand(_curCommand, target);
				}
			}
	
			_curCommand = COMMAND_NONE;
			_cursorState = CURSORSTATE_IDLE;
			_isClicked = false;
			_findTarget = false;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_curCommand = COMMAND_NONE;
			_cursorState = CURSORSTATE_IDLE;
			_isClicked = false;
			_findTarget = false;
		}
		else
		{
			TEAM team = searchObject();

			switch (team)
			{
			case TEAM_NONE:			_cursorState = CURSORSTATE_FOCUS_TO_NEUTRAL;	break;
			case TEAM_NEUTRAL:		_cursorState = CURSORSTATE_FOCUS_TO_NEUTRAL;	break;
			case TEAM_MYTEAM:		_cursorState = CURSORSTATE_FOCUS_TO_ME;			break;
			case TEAM_FRIEND:		_cursorState = CURSORSTATE_FOCUS_TO_NEUTRAL;	break;
			case TEAM_ENEMY:		_cursorState = CURSORSTATE_FOCUS_TO_ENEMY;		break;
			}
		}
		break;

	case CURSORSTATE_ON_ME:
	case CURSORSTATE_ON_NEUTRAL:
	case CURSORSTATE_ON_ENEMY:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isClicked = true;
			_ptDragStart = _ptMouse;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			//위치가 달라지면 드래그상태로 바꾼다.
			if (_ptDragStart.x != _ptMouse.x || _ptDragStart.y != _ptMouse.y)
			{
				_isDraging = true;
				_cursorState = CURSORSTATE_DRAGING;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_isClicked = false;

			if (_selectInfo.isSelected)
			{
				gameObject* target = getTargetInfo();

				if (target == NULL)
				{
					for (int i = 0; i < SELECTUNIT_MAX; i++)
					{
						if (_selectInfo.object[i] == NULL) continue;

						if (_selectInfo.object[i]->getIsBuilding())
						{
							_selectInfo.object[i]->receiveCommand(COMMAND_SETRALLYPOINT, ptMouseReal);
						}
						else
						{
							_selectInfo.object[i]->receiveCommand(COMMAND_MOVE, ptMouseReal);
						}
					}
				}
				else
				{
					for (int i = 0; i < SELECTUNIT_MAX; i++)
					{
						if (_selectInfo.object[i] == NULL) continue;

						if (_selectInfo.object[i]->getIsBuilding())
						{
							_selectInfo.object[i]->receiveCommand(COMMAND_SETRALLYPOINT, ptMouseReal);
						}
						else
						{
							if (target->getPlayerNum() == _playerNum)
							{
								_selectInfo.object[i]->receiveCommand(COMMAND_MOVE, target);
							}
							else
							{
								_selectInfo.object[i]->receiveCommand(COMMAND_ATTACK, target);
							}
						}
					}
				}
			}
		}
		else
		{
			if (_isClicked)
			{
				clickObject();
				_isClicked = false;
			}

			TEAM team = searchObject();
			switch (team)
			{
			case TEAM_NONE:			_cursorState = CURSORSTATE_IDLE;			break;
			case TEAM_NEUTRAL:		_cursorState = CURSORSTATE_ON_NEUTRAL;		break;
			case TEAM_MYTEAM:		_cursorState = CURSORSTATE_ON_ME;			break;
			case TEAM_FRIEND:		_cursorState = CURSORSTATE_ON_NEUTRAL;		break;
			case TEAM_ENEMY:		_cursorState = CURSORSTATE_ON_ENEMY;		break;
			}

		}
		break;

	case CURSORSTATE_DRAGING:
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) == false)
		{
			if (_isDraging)
			{
				//드래그 상태였으면
				_isDraging = false;
				_isClicked = false;
				dragObjects({ _ptDragStart.x, _ptDragStart.y, _ptMouse.x, _ptMouse.y });
			}

			_cursorState = CURSORSTATE_IDLE;
		}
		break;
	case CURSORSTATE_MOVE_LF:
		break;
	case CURSORSTATE_MOVE_LU:
		break;
	case CURSORSTATE_MOVE_UP:
		break;
	case CURSORSTATE_MOVE_RU:
		break;
	case CURSORSTATE_MOVE_RG:
		break;
	case CURSORSTATE_MOVE_RD:
		break;
	case CURSORSTATE_MOVE_DN:
		break;
	case CURSORSTATE_MOVE_LD:
		break;

	case CURSORSTATE_BUILD_NORMAL:		// 건물-기본
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_curCommand = COMMAND_NONE;
			_cursorState = CURSORSTATE_IDLE;
			_isClicked = false;
			_findLocation = false;
		}

		break;
	case CURSORSTATE_BUILD_HATCHERY:	// 건물-해처리
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_curCommand = COMMAND_NONE;
			_cursorState = CURSORSTATE_IDLE;
			_isClicked = false;
			_findLocation = false;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_buildable)
			{
				bool findDrone = false;
				for (int i = 0; i < SELECTUNIT_MAX; i++)
				{
					if (_selectInfo.object[i] == NULL) continue;

					if (_selectInfo.object[i]->getUnitnumZerg() == UNITNUM_ZERG_DRONE)
					{
						POINT ptTileMouseReal;
						ptTileMouseReal.x = (_ptMouse.x + MAINCAMERA->getCameraX()) / TILESIZE;
						ptTileMouseReal.y = (_ptMouse.y + MAINCAMERA->getCameraY()) / TILESIZE;

						POINT ptCenter;
						POINT buildsize = BUILDSIZE_HATCHERY;
						ptCenter.x = ((float)ptTileMouseReal.x + (float)buildsize.x * 0.5f) * TILESIZE;
						ptCenter.y = ((float)ptTileMouseReal.y + (float)buildsize.y * 0.5f) * TILESIZE;

						_selectInfo.object[i]->receiveCommand(_curCommand, ptCenter, ptTileMouseReal);
						findDrone = true;
						break;
					}
				}

				//드론에게 전달했으면, 드론이 없어도 어차피 초기화 해야됨
				_curCommand = COMMAND_NONE;
				_cursorState = CURSORSTATE_IDLE;
				_isClicked = false;
				_findLocation = false;
			}
			else
			{
				//빌드 실패 사운드
			}
		}
		break;
	case CURSORSTATE_BUILD_EXTRACTOR:	// 건물-가스
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_curCommand = COMMAND_NONE;
			_cursorState = CURSORSTATE_IDLE;
			_isClicked = false;
			_findLocation = false;
		}
		break;

	}
}

void gameController::actionMouseMiniMap(void)
{

}
void gameController::actionMouseCommandSet(int num)
{
	int i = num;

	if (_commandSet[i].command == COMMAND_NONE) 
		return;

	if (_commandSet[i].command == COMMAND_ESC)
	{
		_curCommand = COMMAND_NONE;
		_findTarget = false;
		_findLocation = false;
	}
	else
	{
		_curCommand = _commandSet[i].command;
	}
}


void gameController::actionMouseImageFace(void)
{

}


void gameController::calcMouseRealPosition(void)
{
	_cursorPt.x = _ptMouse.x + MAINCAMERA->getCameraX();
	_cursorPt.y = _ptMouse.y + MAINCAMERA->getCameraY();
	_cursorTile.x = (LONG)(_cursorPt.x / TILESIZE);
	_cursorTile.y = (LONG)(_cursorPt.y / TILESIZE);
}

BOOL gameController::actionHotkeys(void)
{
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		if (_commandSet[i].command == COMMAND_NONE) continue;

		if (KEYMANAGER->isOnceKeyDown(_commandSet[i].hotkey))
		{
			if (_commandSet[i].command == COMMAND_ESC)
			{
				_curCommand = COMMAND_NONE;
				_cursorState = CURSORSTATE_IDLE;
				_findTarget = false;
				_findLocation = false;
			}
			else
			{
				_curCommand = _commandSet[i].command;
			}
			return true;
		}
	}

	return false;
}

void gameController::setImageCursor(void)
{
	image* oldImgCursor = _imgCursor;

	if (_isInInterface)
	{
		_imgCursor = IMAGEMANAGER->findImage(L"cursor-Idle");
	}
	else
	{
		switch (_cursorState)
		{
		case CURSORSTATE_IDLE:				_imgCursor = IMAGEMANAGER->findImage(L"cursor-Idle");				break;
		case CURSORSTATE_FOCUS_TO_ME:		_imgCursor = IMAGEMANAGER->findImage(L"cursor-FocusToMe");			break;
		case CURSORSTATE_FOCUS_TO_NEUTRAL:	_imgCursor = IMAGEMANAGER->findImage(L"cursor-FocusToNeutral");		break;
		case CURSORSTATE_FOCUS_TO_ENEMY:	_imgCursor = IMAGEMANAGER->findImage(L"cursor-FocusToEnemy");		break;
		case CURSORSTATE_ON_ME:				_imgCursor = IMAGEMANAGER->findImage(L"cursor-onme");				break;
		case CURSORSTATE_ON_NEUTRAL:		_imgCursor = IMAGEMANAGER->findImage(L"cursor-onneutral");			break;
		case CURSORSTATE_ON_ENEMY:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-onenemy");			break;
		case CURSORSTATE_DRAGING:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-Dragging");			break;
		case CURSORSTATE_MOVE_LF:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-MoveDN");				break;
		case CURSORSTATE_MOVE_LU:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-MoveUP");				break;
		case CURSORSTATE_MOVE_UP:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-MoveLF");				break;
		case CURSORSTATE_MOVE_RU:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-MoveRG");				break;
		case CURSORSTATE_MOVE_RG:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-MoveLU");				break;
		case CURSORSTATE_MOVE_RD:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-MoveLD");				break;
		case CURSORSTATE_MOVE_DN:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-MoveRU");				break;
		case CURSORSTATE_MOVE_LD:			_imgCursor = IMAGEMANAGER->findImage(L"cursor-MoveRD");				break;
		case CURSORSTATE_BUILD_NORMAL:		_imgCursor = IMAGEMANAGER->findImage(L"cursor-Idle");				break; // 건물-기본
		case CURSORSTATE_BUILD_HATCHERY:	_imgCursor = IMAGEMANAGER->findImage(L"cursor-Idle");				break; // 건물-해처리
		case CURSORSTATE_BUILD_EXTRACTOR:	_imgCursor = IMAGEMANAGER->findImage(L"cursor-Idle");				break; // 건물-가스
		}
	}

	if (_imgCursor != oldImgCursor)
	{
		_frameCursor = 0;
		_frameCursorTime = 0.0f;
	}
	else
	{
		float fpsTime = 1 / 10.0f;
		_frameCursorTime += TIMEMANAGER->getElapsedTime();
		if (_frameCursorTime >= fpsTime)
		{
			_frameCursorTime -= fpsTime;

			_frameCursor = (_frameCursor == _imgCursor->getMaxFrameX()) ? 0 : _frameCursor + 1;
		}
	}

	if (_findLocation)
	{
		_buildable = checkBuildable();
	}
}

BOOL gameController::checkBuildable(void)
{
	POINT ptTileMouseReal;
	ptTileMouseReal.x = (_ptMouse.x + MAINCAMERA->getCameraX()) / TILESIZE;
	ptTileMouseReal.y = (_ptMouse.y + MAINCAMERA->getCameraY()) / TILESIZE;

	ZeroMemory(&_buildingPlaceable, sizeof(BUILDSTATE) * OBJECTSIZE_MAX_X * OBJECTSIZE_MAX_Y);

	if (_curCommand == COMMAND_BUILD_HATCHERY)
	{

	}
	else if (_curCommand == COMMAND_BUILD_EXTRACTOR)
	{

	}
	else
	{

	}
	for (int i = 0; i < _buildingSize.x; i++)
	{
		for (int j = 0; j < _buildingSize.y; j++)
		{
			DWORD attribute = _gameMap->getTiles()[ptTileMouseReal.x + i][ptTileMouseReal.y + j].attribute;
			if ((attribute & ATTR_UNBUILD) == ATTR_UNBUILD)
			{
				_buildingPlaceable[i][j] = BUILDSTATE_OVERLAP;
			}
			else
			{
				_buildingPlaceable[i][j] = BUILDSTATE_PLACEABLE;
			}
		}
	}

	for (int i = 0; i < _buildingSize.x; i++)
	{
		for (int j = 0; j < _buildingSize.y; j++)
		{
			if (_buildingPlaceable[i][j] == BUILDSTATE_OVERLAP)
			{
				return false;
			}
		}
	}
	return true;
}

void gameController::renderBuildImage(void)
{
	if (!_findLocation)
		return;


	POINT ptTileMouseReal;
	ptTileMouseReal.x = (_ptMouse.x + MAINCAMERA->getCameraX()) / TILESIZE;
	ptTileMouseReal.y = (_ptMouse.y + MAINCAMERA->getCameraY()) / TILESIZE;

	if (_cursorState == CURSORSTATE_BUILD_HATCHERY)
	{
		//IMAGEMANAGER->frameRender(L"ZB-hatchery", getMemDC(), (ptTileMouseReal.x * TILESIZE) - TILESIZE - MAINCAMERA->getCameraX(), (ptTileMouseReal.y * TILESIZE) - TILESIZE - MAINCAMERA->getCameraY(), 0, 0);
		image* imgHatchery = IMAGEMANAGER->findImage(L"ZB-hatcheryBody");
		RENDERMANAGER->insertImgFrame(ZORDER_GAMEMOUSEDRAG, imgHatchery, (ptTileMouseReal.x * TILESIZE) - TILESIZE - MAINCAMERA->getCameraX(), (ptTileMouseReal.y * TILESIZE) - TILESIZE - MAINCAMERA->getCameraY(), 0, 0);
		
	}
	else if (_cursorState == CURSORSTATE_BUILD_EXTRACTOR)
	{

	}
	else
	{
		switch (_curCommand)
		{
			//BUILD1
		case COMMAND_BUILD_CREEPCOLONY:			;	break;
		case COMMAND_BUILD_SPAWNINGPOOL:		;	break;
		case COMMAND_BUILD_EVOLUTIONCHAMBER:	;	break;
		case COMMAND_BUILD_HYDRALISKDEN:		;	break;
			//BUILD2
		case COMMAND_BUILD_SPIRE:				;	break;
		case COMMAND_BUILD_QUEENSNEST:			;	break;
		case COMMAND_BUILD_NYDUSCANAL:			;	break;
		case COMMAND_BUILD_ULTRALISKCAVERN:		;	break;
		case COMMAND_BUILD_DEFILERMOUND:		;	break;
		}
	}

	image* imgEnableTile = IMAGEMANAGER->findImage(L"maptool-object-enableTile");
	image* imgDisableTile = IMAGEMANAGER->findImage(L"maptool-object-disableTile");

	for (int i = 0; i < _buildingSize.x; i++)
	{
		for (int j = 0; j < _buildingSize.y; j++)
		{
			if (_buildingPlaceable[i][j] == BUILDSTATE_PLACEABLE)
			{
				//IMAGEMANAGER->alphaRender(L"maptool-object-enableTile", getMemDC(),
				//	(ptTileMouseReal.x + i) * TILESIZE - MAINCAMERA->getCameraX(), (ptTileMouseReal.y + j) * TILESIZE - MAINCAMERA->getCameraY(), 128);

				RENDERMANAGER->insertImgAlpha(ZORDER_GAMEMOUSEDRAG, imgEnableTile, (ptTileMouseReal.x + i) * TILESIZE - MAINCAMERA->getCameraX(), (ptTileMouseReal.y + j) * TILESIZE - MAINCAMERA->getCameraY(), 128);
			}
			else if (_buildingPlaceable[i][j] == BUILDSTATE_OVERLAP)
			{
				//IMAGEMANAGER->alphaRender(L"maptool-object-disableTile", getMemDC(),
				//	(ptTileMouseReal.x + i) * TILESIZE - MAINCAMERA->getCameraX(), (ptTileMouseReal.y + j) * TILESIZE - MAINCAMERA->getCameraY(), 128);

				RENDERMANAGER->insertImgAlpha(ZORDER_GAMEMOUSEDRAG, imgDisableTile, (ptTileMouseReal.x + i) * TILESIZE - MAINCAMERA->getCameraX(), (ptTileMouseReal.y + j) * TILESIZE - MAINCAMERA->getCameraY(), 128);
			}
		}
	}
}


void gameController::renderCursor(void)
{
	if (_imgCursor == NULL)
		return;

	if (_isInInterface)
	{
		//_imgCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
		RENDERMANAGER->insertImgFrame(ZORDER_MOUSECURSOR, _imgCursor, _ptMouse.x, _ptMouse.y, _frameCursor, 0);
	}
	else
	{
		switch (_cursorState)
		{
		case CURSORSTATE_IDLE:				
			//_imgCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);		
			RENDERMANAGER->insertImgFrame(ZORDER_MOUSECURSOR, _imgCursor, _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			break;
		case CURSORSTATE_FOCUS_TO_ME:		
		case CURSORSTATE_FOCUS_TO_NEUTRAL:	
		case CURSORSTATE_FOCUS_TO_ENEMY:	
		case CURSORSTATE_ON_ME:				
		case CURSORSTATE_ON_NEUTRAL:		
		case CURSORSTATE_ON_ENEMY:			
			//_imgCursor->frameRenderCT(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);		
			RENDERMANAGER->insertImgFrameCC(ZORDER_MOUSECURSOR, _imgCursor, _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			break;
		case CURSORSTATE_DRAGING:			
			//_imgCursor->renderCT(getMemDC(), _ptMouse.x, _ptMouse.y);
			RENDERMANAGER->insertImgCT(ZORDER_MOUSECURSOR, _imgCursor, _ptMouse.x, _ptMouse.y);
			break;
		case CURSORSTATE_MOVE_LF:
		case CURSORSTATE_MOVE_LU:
		case CURSORSTATE_MOVE_UP:
		case CURSORSTATE_MOVE_RU:
		case CURSORSTATE_MOVE_RG:
		case CURSORSTATE_MOVE_RD:
		case CURSORSTATE_MOVE_DN:
		case CURSORSTATE_MOVE_LD:
			//_imgCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			RENDERMANAGER->insertImgFrame(ZORDER_MOUSECURSOR, _imgCursor, _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			break;
		case CURSORSTATE_BUILD_NORMAL:		// 건물-기본
			//_imgCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			RENDERMANAGER->insertImgFrame(ZORDER_MOUSECURSOR, _imgCursor, _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			//건물이미지
			break;
		case CURSORSTATE_BUILD_HATCHERY:	// 건물-해처리
			//_imgCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			RENDERMANAGER->insertImgFrame(ZORDER_MOUSECURSOR, _imgCursor, _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			//건물이미지
			break;
		case CURSORSTATE_BUILD_EXTRACTOR:	// 건물-가스
			//_imgCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			RENDERMANAGER->insertImgFrame(ZORDER_MOUSECURSOR, _imgCursor, _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			//건물이미지
			//
			break;
		}
	}
}

void gameController::renderInterface(void)
{
	if (_imgInterface == NULL)
		return;

	RENDERMANAGER->insertImg(ZORDER_INTERFACE, _imgInterface, 0, 0);

	//선택된 유닛, 건물의 정보를 보여준다.
	renderSelectInfo();

	//선택된 유닛, 건물의 커맨드를 보여준다.
	renderCommands();

	//미니맵을 보여준다.
	_miniMap->render();
}

void gameController::renderSelectInfo(void)
{
	if (_selectInfo.num == 0)
	{
		return;
	}
	else if (_selectInfo.num == 1)
	{
		tagBaseStatus baseStatus = _selectInfo.object[0]->getBaseStatus();
		tagBattleStatus battleStatus = _selectInfo.object[0]->getBattleStatus();

		if (battleStatus.isDead)
		{
			_selectInfo.object[0] = NULL;
		}
		else
		{
			//COLORREF oldColor = GetTextColor(getMemDC());

			//이미지
			RENDERMANAGER->insertImg(ZORDER_INTERFACE, baseStatus.imgStat1, 153, 374);

			//HP
			RECT rcHP = RectMake(178, 453, 80, 12);
			TCHAR strHP[100];
			_stprintf(strHP, L"%d / %d", (INT)battleStatus.curHP, (INT)battleStatus.maxHP);

			//SetTextColor(getMemDC(), TEXTCOLOR_UNITHP);
			//DrawText(getMemDC(), strHP, _tcslen(strHP), &rcHP, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			RENDERMANAGER->insertText(ZORDER_INTERFACE, rcHP, strHP, TEXTCOLOR_UNITHP);

			if (baseStatus.useMP)
			{
				//MP
				RECT rcMP = RectMake(178, 470, 43, 12);
				TCHAR strMP[100];
				_stprintf(strMP, L"%d / %d", (INT)battleStatus.curMP, (INT)battleStatus.maxMP);
				//SetTextColor(getMemDC(), TEXTCOLOR_UNITMP);
				//DrawText(getMemDC(), strMP, _tcslen(strMP), &rcMP, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				RENDERMANAGER->insertText(ZORDER_INTERFACE, rcMP, strMP, TEXTCOLOR_UNITMP);
			}


			//SetTextColor(getMemDC(), oldColor);
		}
	}
	else
	{
		for (int i = 0; i < SELECTUNIT_MAX; i++)
		{
			if (_selectInfo.object[i] == NULL) continue;
		}
	}
}


void gameController::renderCommands(void)
{
	if (_selectInfo.isSelected == FALSE)
		return;

	for (int i = 0; i < COMMAND_MAX; i++)
	{
		//_commandSet[i].button->render();
		_commandSet[i].button->ZRender(ZORDER_INTERFACE);

		//if (_commandSet[i].img == NULL) continue;
		//_commandSet[i].img->render(getMemDC(), _commandSet[i].rc.left, _commandSet[i].rc.top);
	}
}

TEAM gameController::searchObject(void)
{
	POINT ptMouseReal;
	ptMouseReal.x = _ptMouse.x + MAINCAMERA->getCameraX();
	ptMouseReal.y = _ptMouse.y + MAINCAMERA->getCameraY();

	//TARGETTYPE targetType = TARGETTYPE_GROUND;
	//void* res = getTargetInfo(ptMouseReal, targetType);

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player* player = _player[i];
		vUnits vUnitsInCamera = player->getUnitsInCamera();
		vBuildings vBuildingsInCamera = player->getBuildingsInCamera();

		//유닛먼저 체크
		for (int j = 0; j < vUnitsInCamera.size(); j++)
		{
			RECT rcBody = vUnitsInCamera[j]->getBattleStatus().rcBody;
			if (PtInRect(&rcBody, ptMouseReal))
			{
				if (i == PLAYER1)
				{
					return TEAM_MYTEAM;
				}
				else
				{
					return TEAM_ENEMY;
				}
			}
		}

		//유닛 체크 안되면 건물 체크
		for (int j = 0; j < vBuildingsInCamera.size(); j++)
		{
			RECT rcBody = vBuildingsInCamera[j]->getBattleStatus().rcBody;
			if (PtInRect(&rcBody, ptMouseReal))
			{
				if (i == PLAYER1)
				{
					return TEAM_MYTEAM;
				}
				else
				{
					return TEAM_ENEMY;
				}
			}
		}

	}
	return TEAM_NONE;
}

TEAM gameController::clickObject(void)
{
	POINT ptMouseReal;
	ptMouseReal.x = _ptMouse.x + MAINCAMERA->getCameraX();
	ptMouseReal.y = _ptMouse.y + MAINCAMERA->getCameraY();

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player* player = _player[i];
		vUnits vUnitsInCamera = player->getUnitsInCamera();
		vBuildings vBuildingsInCamera = player->getBuildingsInCamera();

		//유닛먼저 체크
		for (int j = 0; j < vUnitsInCamera.size(); j++)
		{
			RECT rcBody = vUnitsInCamera[j]->getBattleStatus().rcBody;
			if (PtInRect(&rcBody, ptMouseReal))
			{
				if (i == PLAYER1)
				{
					vUnitsInCamera[j]->setClicked(true);

					_selectInfo.isSelected = true;
					_selectInfo.num = 1;
					_selectInfo.object[0] = vUnitsInCamera[j];

					return TEAM_MYTEAM;
				}
			}
		}
	}

	return TEAM_NONE;

}

TEAM gameController::dragObjects(RECT rcDrag)
{
	rcDrag.left   += MAINCAMERA->getCameraX();
	rcDrag.right  += MAINCAMERA->getCameraX();
	rcDrag.top    += MAINCAMERA->getCameraY();
	rcDrag.bottom += MAINCAMERA->getCameraY();

	if (rcDrag.right < rcDrag.left)
	{
		LONG temp = rcDrag.right;
		rcDrag.right = rcDrag.left;
		rcDrag.left = temp;
	}

	if (rcDrag.bottom < rcDrag.top)
	{
		LONG temp = rcDrag.bottom;
		rcDrag.bottom = rcDrag.top;
		rcDrag.top = temp;
	}

	RECT temp;

	UINT unitNum = 0;
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player* player = _player[i];
		vUnits vUnitsInCamera = player->getUnitsInCamera();
		vBuildings vBuildingsInCamera = player->getBuildingsInCamera();

		//유닛먼저 체크
		for (int j = 0; j < vUnitsInCamera.size(); j++)
		{
			RECT rcBody = vUnitsInCamera[j]->getBattleStatus().rcBody;
			if (IntersectRect(&temp, &rcBody, &rcDrag))
			{
				if (i == PLAYER1)
				{
					vUnitsInCamera[j]->setClicked(true);

					_selectInfo.isSelected = true;
					_selectInfo.object[unitNum] = vUnitsInCamera[j];

					unitNum++;

					if (unitNum == SELECTUNIT_MAX) break;
				}
			}
		}

		if (unitNum > 0)
		{
			_selectInfo.num = unitNum;
			return TEAM_MYTEAM;
		}


	}

	return TEAM_NONE;

}


gameObject* gameController::getTargetInfo(void)
{
	POINT ptMouseReal;
	ptMouseReal.x = _ptMouse.x + MAINCAMERA->getCameraX();
	ptMouseReal.y = _ptMouse.y + MAINCAMERA->getCameraY();

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		player* player = _player[i];
		vUnits vUnitsInCamera = player->getUnitsInCamera();
		vBuildings vBuildingsInCamera = player->getBuildingsInCamera();

		//유닛먼저 체크
		for (int j = 0; j < vUnitsInCamera.size(); j++)
		{
			RECT rcBody = vUnitsInCamera[j]->getBattleStatus().rcBody;
			if (PtInRect(&rcBody, ptMouseReal))
			{
				return vUnitsInCamera[j];
			}
		}

		//유닛 체크 안되면 건물 체크
		//for (int j = 0; j < vBuildingsInCamera.size(); j++)
		//{
		//	if (PtInRect(&(vBuildingsInCamera[j]->getBattleStatus().rcBody), ptMouseReal))
		//	{
		//		if (i == PLAYER1)
		//		{
		//			return TEAM_MYTEAM;
		//		}
		//	}
		//}

	}
	return NULL;
}


void gameController::actionCommand(void)
{
	switch (_curCommand)
	{
	case COMMAND_NONE:
		break;
	case COMMAND_ESC:
		break;
	case COMMAND_MOVE:
	case COMMAND_ATTACK:
	case COMMAND_PATROL:
	case COMMAND_GATHER:
		_findTarget = true;
		break;
	case COMMAND_STOP:
	case COMMAND_HOLD:
	case COMMAND_RETURNCARGO:
	case COMMAND_BURROW:
	case COMMAND_UNBURROW:
		for (int i = 0; i < SELECTUNIT_MAX; i++)
		{
			if (_selectInfo.object[i] == NULL) continue;
			_selectInfo.object[i]->receiveCommand(_curCommand);
		}
		_curCommand = COMMAND_NONE;
		break;
	case COMMAND_BUILD1:
		break;
	case COMMAND_BUILD2:
		break;
	case COMMAND_SELECT_LARVA:
		if (_selectInfo.object[0]->getBuildingNumZerg() == BUILDINGNUM_ZERG_HATCHERY)
		{
			zbHatchery* hatchery = (zbHatchery*)_selectInfo.object[0];
			vector<zuLarva*> larvas = hatchery->getLarvas();
			if (larvas.size() > 0)
			{
				_selectInfo.object[0]->setClicked(false);
				_selectInfo.object[0] = NULL;
				_selectInfo.num = 0;

				for (int i = 0; i < larvas.size(); i++)
				{
					larvas[i]->setClicked(true);
					_selectInfo.object[i] = larvas[i];
					_selectInfo.num++;
				}
			}
		}
		else if (_selectInfo.object[0]->getBuildingNumZerg() == BUILDINGNUM_ZERG_LAIR)
		{
			zbLair* lair = (zbLair*)_selectInfo.object[0];
			vector<zuLarva*> larvas = lair->getLarvas();
			if (larvas.size() > 0)
			{
				_selectInfo.object[0]->setClicked(false);
				_selectInfo.object[0] = NULL;
				_selectInfo.num = 0;

				for (int i = 0; i < larvas.size(); i++)
				{
					larvas[i]->setClicked(true);
					_selectInfo.object[i] = larvas[i];
					_selectInfo.num++;
				}
			}
		}
		else if (_selectInfo.object[0]->getBuildingNumZerg() == BUILDINGNUM_ZERG_HIVE)
		{
			zbHive* hive = (zbHive*)_selectInfo.object[0];
			vector<zuLarva*> larvas = hive->getLarvas();
			if (larvas.size() > 0)
			{
				_selectInfo.object[0]->setClicked(false);
				_selectInfo.object[0] = NULL;
				_selectInfo.num = 0;

				for (int i = 0; i < larvas.size(); i++)
				{
					larvas[i]->setClicked(true);
					_selectInfo.object[i] = larvas[i];
					_selectInfo.num++;
				}
			}
		}
		_curCommand = COMMAND_NONE;
		break;
	case COMMAND_SETRALLYPOINT:
		break;


		//ZERG
	case COMMAND_INFEST:					_findTarget = true;		break;
	case COMMAND_PARASITE:					_findTarget = true;		break;
	case COMMAND_BROODRING:					_findTarget = true;		break;
	case COMMAND_ENSNARE:					_findTarget = true;		break;
	case COMMAND_CONSUME:					_findTarget = true;		break;
	case COMMAND_DARKSWARM:					_findTarget = true;		break;
	case COMMAND_PLAGUE:					_findTarget = true;		break;

		//BUILD1
	case COMMAND_BUILD_HATCHERY:			_findLocation = true;	_buildingSize = BUILDSIZE_HATCHERY			;	_buildable = false; break;
	case COMMAND_BUILD_LAIR:				break;
	case COMMAND_BUILD_HIVE:				break;
	case COMMAND_BUILD_CREEPCOLONY:			_findLocation = true;	_buildingSize = BUILDSIZE_CREEPCOLONY		;	_buildable = false; break;
	case COMMAND_BUILD_SUNKENCOLONY:		break;
	case COMMAND_BUILD_SPORECOLONY:			break;
	case COMMAND_BUILD_EXTRACTOR:			_findLocation = true;	_buildingSize = BUILDSIZE_EXTRACTOR			;	_buildable = false; break;
	case COMMAND_BUILD_SPAWNINGPOOL:		_findLocation = true;	_buildingSize = BUILDSIZE_SPAWNINGPOOL		;	_buildable = false; break;
	case COMMAND_BUILD_EVOLUTIONCHAMBER:	_findLocation = true;	_buildingSize = BUILDSIZE_EVOLUTIONCHAMBER	;	_buildable = false; break;
	case COMMAND_BUILD_HYDRALISKDEN:		_findLocation = true;	_buildingSize = BUILDSIZE_HYDRALISKDEN		;	_buildable = false; break;
		//BUILD2
	case COMMAND_BUILD_SPIRE:				_findLocation = true;	_buildingSize = BUILDSIZE_SPIRE				;	_buildable = false; break;
	case COMMAND_BUILD_GREATERSPIRE:		break;
	case COMMAND_BUILD_QUEENSNEST:			_findLocation = true;	_buildingSize = BUILDSIZE_QUEENSNEST		;	_buildable = false; break;
	case COMMAND_BUILD_NYDUSCANAL:			_findLocation = true;	_buildingSize = BUILDSIZE_NYDUSCANAL		;	_buildable = false; break;
	case COMMAND_BUILD_ULTRALISKCAVERN:		_findLocation = true;	_buildingSize = BUILDSIZE_ULTRALISKCAVERN	;	_buildable = false; break;
	case COMMAND_BUILD_DEFILERMOUND:		_findLocation = true;	_buildingSize = BUILDSIZE_DEFILERMOUND		;	_buildable = false; break;

		//UNIT
	case COMMAND_UNIT_DRONE:
		for (int i = 0; i < SELECTUNIT_MAX; i++)
		{
			if (_selectInfo.object[i] == NULL) continue;
			_selectInfo.object[i]->receiveCommand(_curCommand);
		}
		_curCommand = COMMAND_NONE;
		break;

	case COMMAND_UNIT_ZERGLING:				break;
	case COMMAND_UNIT_OVERLORD:				break;
	case COMMAND_UNIT_HYDRALISK:			break;
	case COMMAND_UNIT_MUTALISK:				break;
	case COMMAND_UNIT_SCOURGE:				break;
	case COMMAND_UNIT_QUEEN:				break;
	case COMMAND_UNIT_ULTRALISK:			break;
	case COMMAND_UNIT_DEFILER:				break;
		//UNIT2
	case COMMAND_UNIT_LURKER:				break;
	case COMMAND_UNIT_GUADIAN:				break;
	case COMMAND_UNIT_DEVOURER:				break;
	case COMMAND_UNIT_INFESTEDTERRAN:		break;

		//UPGRADE
	case COMMAND_UPGRADE_ZERG_MELEEATTACKS:				break; //저그 지상유닛 근접 공격
	case COMMAND_UPGRADE_ZERG_MISSILEATTACKS:			break; //저그 지상유닛 원거리 공격
	case COMMAND_UPGRADE_ZERG_CARAPACE:					break; //저그 지상유닛 방어력
	case COMMAND_UPGRADE_ZERG_FLYERATTACKS:				break; //저그 공중유닛 공격
	case COMMAND_UPGRADE_ZERG_FLYERCARAPACE:			break; //저그 공중유닛 방어력

		//EVOLUTION
	case COMMAND_EVOLUTION_ZERG_EVOLVE_BURROW:			break; //저그 버러우 업글
	case COMMAND_EVOLUTION_ZERG_METABOLICK_BOOST:		break; //저글링 이속업
	case COMMAND_EVOLUTION_ZERG_ADRENAL_GLANDS:			break; //저글링 아드레날린
	case COMMAND_EVOLUTION_ZERG_VECTRAL_SACS:			break; //오버로드 수송업
	case COMMAND_EVOLUTION_ZERG_ANTENNAE:				break; //오버로드 시야업
	case COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:	break; //오버로드 이속업
	case COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS:		break; //히드라 이속업
	case COMMAND_EVOLUTION_ZERG_GROOVED_SPINES:			break; //히드라 사정거리업
	case COMMAND_EVOLUTION_ZERG_EVOLVE_LURKER_ASPECT:	break; //럴커 업글
	case COMMAND_EVOLUTION_ZERG_EVOLVE_SPAWN_BROODLING:	break; //퀸 브루드링 업글
	case COMMAND_EVOLUTION_ZERG_EVOLVE_ENSNARE:			break; //퀸 인스테어 업글
	case COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS:			break; //퀸 마나업
	case COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:		break; //울트라 이송업
	case COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING:		break; //울트라 방업(+2)
	case COMMAND_EVOLUTION_ZERG_EVOLVE_PLAGUE:			break; //디파일러 플레이그
	case COMMAND_EVOLUTION_ZERG_EVOLVE_CONSUME:			break; //디파일러 컨슘
	case COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE:		break; //디파일러 마나업

	}

}

void gameController::setCommandSet(void)
{
	if (_selectInfo.isSelected == FALSE)
		return;

	//선택 되었어도 죽어서 없어졌는지 다시 체크
	int realUnitNum = 0;

	for (int i = 0; i < SELECTUNIT_MAX; i++)
	{
		if (_selectInfo.object[i] == NULL)
		{
			continue;
		}
		realUnitNum++;
	}

	if (realUnitNum == 0)
	{
		_selectInfo.isSelected = false;
		return;
	}
	_selectInfo.num = realUnitNum;

	//유닛에게 커맨드 상태, 커맨드셋 받아오기
	if (realUnitNum == 1)
	{
		_unitCommandInfo = _selectInfo.object[0]->getBattleStatus().curCommand;
		memcpy(_commandSetUnit, _selectInfo.object[0]->getBaseStatus().commands, sizeof(COMMAND)*COMMAND_MAX);
	}
	else
	{
		//유닛이 복수일 경우
		//0. 라바, 에그, 일반유닛 구분
		//1. 모두 같은 유닛인지 체크 (->TRUE : 커맨드 모두 그대로 감 (드론은 빌드 제외))
		//2. 다른 유닛일 경우 모두 지상유닛인지 체크 (->TRUE : 버러우 가능한 유닛이 있으면 버러우 커맨드 추가)
		//3. 공격 불가능한 유닛들만 있는지 체크 (-> 공격 커맨드 빼야됨)
		//4. 

	}






	//debug
	switch (_curCommand)
	{
	case COMMAND_BUILD1:
		for (int i = 0; i < COMMAND_MAX; i++)
		{
			_commandSet[i].command = _commandSetBuild1[i];
		}
		break;
	case COMMAND_BUILD2:
		for (int i = 0; i < COMMAND_MAX; i++)
		{
			_commandSet[i].command = _commandSetBuild2[i];
		}
		break;
	default:
		if (_findTarget || _findLocation)
		{
			for (int i = 0; i < COMMAND_MAX; i++)
			{
				_commandSet[i].command = _commandSetEsc[i];
			}
		}
		else
		{
			for (int i = 0; i < COMMAND_MAX; i++)
			{
				_commandSet[i].command = _commandSetUnit[i];
			}
		}
		break;
	}

	//커맨드 핫키 매칭
	matchingCommandHotkey();
	//커맨드 이미지 매칭
	matchingCommandImage();
}

void gameController::matchingCommandHotkey(void)
{
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		_commandSet[i].hotkey = _hotkeys->getHotkey(_commandSet[i].command);
	}
}

void gameController::matchingCommandImage(void)
{
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		//image matching
		switch (_commandSet[i].command)
		{
			//COMMON
			case COMMAND_NONE:
			{
				_commandSet[i].button->setImage(L"");

				_commandSet[i].button->setDisable(true);
				_commandSet[i].button->setOnlyDown(false);
				

				break;
			}
			case COMMAND_ESC:
			{
				_commandSet[i].button->setImage(L"command-esc");

				_commandSet[i].button->setDisable(false);
				_commandSet[i].button->setOnlyDown(false);

				break;
			}
			case COMMAND_MOVE:
			{
				_commandSet[i].button->setImage(L"command-move");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_STOP:
			{
				_commandSet[i].button->setImage(L"command-stop");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_ATTACK:
			{
				_commandSet[i].button->setImage(L"command-attack");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_PATROL:
			{
				_commandSet[i].button->setImage(L"command-patrol");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_HOLD:
			{
				_commandSet[i].button->setImage(L"command-hold");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_GATHER:
			{
				_commandSet[i].button->setImage(L"command-gather");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_RETURNCARGO:
			{
				_commandSet[i].button->setImage(L"command-return");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD1:
			{
				_commandSet[i].button->setImage(L"command-build1");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD2:
			{
				_commandSet[i].button->setImage(L"command-build2");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);

				break;
			}
			case COMMAND_SELECT_LARVA:
			{
				_commandSet[i].button->setImage(L"command-select_larva");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);

				break;
			}
			case COMMAND_SETRALLYPOINT:
			{
				_commandSet[i].button->setImage(L"command-set_rally_point");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);

				break;
			}

			//ZERG
			case COMMAND_BURROW:
			{
				_commandSet[i].button->setImage(L"command-burrow");

				if (_myPlayer->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_EVOLVE_BURROW].complete)
				{
					_commandSet[i].button->setDisable(false);
				}
				else
				{
					_commandSet[i].button->setDisable(true);
				}

				_commandSet[i].button->setOnlyDown(false);
				

				break;
			}
			case COMMAND_UNBURROW:
			{
				_commandSet[i].button->setImage(L"command-unburrow");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_INFEST:
			{
				_commandSet[i].button->setImage(L"command-infest");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_PARASITE:
			{
				_commandSet[i].button->setImage(L"command-parasite");

				_commandSet[i].button->setDisable(false);
				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BROODRING:
			{
				_commandSet[i].button->setImage(L"command-broodring");

				if (_myPlayer->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_EVOLVE_SPAWN_BROODLING].complete)
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_ENSNARE:
			{
				_commandSet[i].button->setImage(L"command-ensnare");

				if (_myPlayer->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_EVOLVE_ENSNARE].complete)
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				if (_unitCommandInfo == _commandSet[i].command)
					_commandSet[i].button->setOnlyDown(true);
				else
					_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_CONSUME:
			{
				_commandSet[i].button->setImage(L"command-consume");

				if (_myPlayer->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_EVOLVE_CONSUME].complete)
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				_commandSet[i].button->setOnlyDown(false);
				
				break;
			}
			case COMMAND_DARKSWARM:
			{
				_commandSet[i].button->setImage(L"command-darkswarm");

				_commandSet[i].button->setDisable(false);
				_commandSet[i].button->setOnlyDown(false);
				
				break;
			}
			case COMMAND_PLAGUE:
			{
				_commandSet[i].button->setImage(L"command-plague");

				if (_myPlayer->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_EVOLVE_PLAGUE].complete)
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				_commandSet[i].button->setOnlyDown(false);
				
				break;
			}
			//BUILD
			case COMMAND_BUILD_HATCHERY:
			{
				_commandSet[i].button->setImage(L"command-build_hatchery");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_LAIR:
			{
				_commandSet[i].button->setImage(L"command-build_lair");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_SPAWNINGPOOL))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_HIVE:
			{
				_commandSet[i].button->setImage(L"command-build_hive");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_QUEENSNEST))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_CREEPCOLONY:
			{
				_commandSet[i].button->setImage(L"command-build_creepcolony");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_BUILD_SUNKENCOLONY:
			{
				_commandSet[i].button->setImage(L"command-build_sunkencolony");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_SPAWNINGPOOL))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_BUILD_SPORECOLONY:
			{
				_commandSet[i].button->setImage(L"command-build_sporecolony");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_EVOLUTIONCHAMBER))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_EXTRACTOR:
			{
				_commandSet[i].button->setImage(L"command-build_extractor");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_SPAWNINGPOOL:
			{
				_commandSet[i].button->setImage(L"command-build_spawningpool");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HATCHERY)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_LAIR)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_EVOLUTIONCHAMBER:
			{
				_commandSet[i].button->setImage(L"command-build_evolutionchamber");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HATCHERY)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_LAIR)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_BUILD_HYDRALISKDEN:
			{
				_commandSet[i].button->setImage(L"command-build_hydraliskden");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_SPAWNINGPOOL))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_SPIRE:
			{
				_commandSet[i].button->setImage(L"command-build_spire");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_LAIR)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_BUILD_GREATERSPIRE:
			{
				_commandSet[i].button->setImage(L"command-build_greaterspire");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_BUILD_QUEENSNEST:
			{
				_commandSet[i].button->setImage(L"command-build_queensnest");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_LAIR)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_NYDUSCANAL:
			{
				_commandSet[i].button->setImage(L"command-build_nyduscanal");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_ULTRALISKCAVERN:
			{
				_commandSet[i].button->setImage(L"command-build_ultraliskcavern");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_BUILD_DEFILERMOUND:
			{
				_commandSet[i].button->setImage(L"command-build_defilermound");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			//UNIT
			case COMMAND_UNIT_DRONE:
			{
				_commandSet[i].button->setImage(L"command-unit_drone");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_UNIT_ZERGLING:
			{
				_commandSet[i].button->setImage(L"command-unit_zergling");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_SPAWNINGPOOL))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_UNIT_OVERLORD:
			{
				_commandSet[i].button->setImage(L"command-unit_overlord");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_UNIT_HYDRALISK:
			{
				_commandSet[i].button->setImage(L"command-unit_hydralisk");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HYDRALISKDEN))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_UNIT_MUTALISK:
			{
				_commandSet[i].button->setImage(L"command-unit_mutalisk");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_SPIRE)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_GREATERSPIRE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_UNIT_SCOURGE:
			{
				_commandSet[i].button->setImage(L"command-unit_scourge");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_SPIRE)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_GREATERSPIRE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_UNIT_QUEEN:
			{
				_commandSet[i].button->setImage(L"command-unit_queen");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_QUEENSNEST))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_UNIT_ULTRALISK:
			{
				_commandSet[i].button->setImage(L"command-unit_ultralisk");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_ULTRALISKCAVERN))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_UNIT_DEFILER:
			{
				_commandSet[i].button->setImage(L"command-unit_defiler");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_DEFILERMOUND))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_UNIT_LURKER:
			{
				_commandSet[i].button->setImage(L"command-unit_lurker");

				if (_myPlayer->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_EVOLVE_LURKER_ASPECT].complete)
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_UNIT_GUADIAN:
			{
				_commandSet[i].button->setImage(L"command-unit_guadian");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_GREATERSPIRE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_UNIT_DEVOURER:
			{
				_commandSet[i].button->setImage(L"command-unit_devourer");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_GREATERSPIRE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			case COMMAND_UNIT_INFESTEDTERRAN:
			{
				_commandSet[i].button->setImage(L"command-unit_infestedterran");

				_commandSet[i].button->setDisable(false);
				
				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			//UPGRADE
			case COMMAND_UPGRADE_ZERG_MELEEATTACKS:				//저그 지상유닛 근접 공격
			{
				_commandSet[i].button->setImage(L"command-upgrade_zerg_meleeattacks");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_UPGRADE_ZERG_MISSILEATTACKS:			//저그 지상유닛 원거리 공격
			{
				_commandSet[i].button->setImage(L"command-upgrade_zerg_missileattacks");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_UPGRADE_ZERG_CARAPACE:					//저그 지상유닛 방어력
			{
				_commandSet[i].button->setImage(L"command-upgrade_zerg_carapace");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_UPGRADE_ZERG_FLYERATTACKS:				//저그 공중유닛 공격
			{
				_commandSet[i].button->setImage(L"command-upgrade_zerg_flyerattacks");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_UPGRADE_ZERG_FLYERCARAPACE:			//저그 공중유닛 방어력
			{
				_commandSet[i].button->setImage(L"command-upgrade_zerg_flyercarapace");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}

			//EVOLUTION
			case COMMAND_EVOLUTION_ZERG_EVOLVE_BURROW:			//저그 버러우 업글
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_evolve_burrow");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_METABOLICK_BOOST:		//저글링 이속업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_metabolick_boost");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_ADRENAL_GLANDS:			//저글링 아드레날린
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_adrenal_glands");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_VECTRAL_SACS:			//오버로드 수송업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_vectral_sacs");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_ANTENNAE:				//오버로드 시야업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_antennae");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:	//오버로드 이속업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_pneumatized_carapace");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS:		//히드라 이속업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_muscular_augments");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_GROOVED_SPINES:			//히드라 사정거리업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_grooved_spines");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_EVOLVE_LURKER_ASPECT:	//럴커 업글
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_evolve_lurker_aspect");

				if (_myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_LAIR)
					|| _myPlayer->isHaveBuilding(BUILDINGNUM_ZERG_HIVE))
					_commandSet[i].button->setDisable(false);
				else
					_commandSet[i].button->setDisable(true);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_EVOLVE_SPAWN_BROODLING:	//퀸 브루드링 업글
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_evolve_spawn_broodling");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_EVOLVE_ENSNARE:			//퀸 인스테어 업글
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_evolve_ensnare");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS:			//퀸 마나업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_gamete_meiosis");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:		//울트라 이송업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_anabolic_synthesis");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING:		//울트라 방업(+2)
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_chitinous_plating");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_EVOLVE_PLAGUE:			//디파일러 플레이그
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_evolve_plague");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_EVOLVE_CONSUME:			//디파일러 컨슘
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_evolve_consume");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}
			case COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE:		//디파일러 마나업
			{
				_commandSet[i].button->setImage(L"command-evolution_zerg_metasynaptic_node");

				_commandSet[i].button->setDisable(false);

				_commandSet[i].button->setOnlyDown(false);
				break;
			}

		}
	}
}

void gameController::changeSelectInfoToNextObect(gameObject* object)
{
	if (_selectInfo.isSelected == false)
		return;

	for (int i = 0; i < SELECTUNIT_MAX; i++)
	{
		if (_selectInfo.object[i] == object)
		{
			_selectInfo.object[i] = object->getNextObject();
			return;
		}
	}
}