#include "stdafx.h"
#include "gameController.h"


gameController::gameController()
	: _imgInterface(NULL), _imgCursor(NULL)
{
	_cursorState = CURSORSTATE_IDLE;

	_command = 0;
	ZeroMemory(&_unitCommandInfo, sizeof(tagUnitCommands));


	ZeroMemory(&_selectInfo, sizeof(tagSelectInfo));


}


gameController::~gameController()
{
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

	initCommandRect();

	//debug
	_isInInterface = false;
	_isDraging = false;
	

	return S_OK;
}

void gameController::release(void)
{
}

void gameController::update(void)
{
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
			actionMouseInterface();
		}
	}

	setCommandSet();
	setImageCursor();
}

void gameController::render(void)
{

	if(_isDraging)
	{
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), _gPen[PENVERSION_MOUSEDRAG]);
		//Rectangle(getMemDC(), _ptDragStart.x, _ptDragStart.y, _ptMouse.x, _ptMouse.y);
		LineMake(getMemDC(), _ptDragStart.x, _ptDragStart.y, _ptMouse.x, _ptDragStart.y);
		LineMake(getMemDC(), _ptDragStart.x, _ptDragStart.y, _ptDragStart.x, _ptMouse.y);
		LineMake(getMemDC(), _ptMouse.x, _ptMouse.y, _ptDragStart.x, _ptMouse.y);
		LineMake(getMemDC(), _ptMouse.x, _ptMouse.y, _ptMouse.x, _ptDragStart.y);
		SelectObject(getMemDC(), oldPen);
		DeleteObject(oldPen);
	}


	renderInterface();
	renderCommands();


	renderCursor();
}

void gameController::initCommandRect(void)
{
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		int idx = i % 3;
		int idy = i / 3;

		//_unitCommandInfo.rc[i] = RectMake(1013 + idx * 92, 717 + idx * 80, 68, 66);
		_unitCommandInfo.rc[i] = RectMake(506 + idx * 46, 358 + idy * 40, 34, 33);

	}
}

void gameController::actionMouseInterface(void)
{

}

void gameController::actionMouseMap(void)
{
	POINT ptMouseReal;
	ptMouseReal.x = _ptMouse.x + MAINCAMERA->getCameraX();
	ptMouseReal.y = _ptMouse.y + MAINCAMERA->getCameraY();

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
	else
	{
		TEAM team = TEAM_NONE;

		if (_isDraging)
		{
			//드래그 상태였으면
			_isDraging = false;
			_isClicked = false;
			dragObjects(RectMake(_ptDragStart.x, _ptDragStart.y, _ptMouse.x, _ptMouse.y));
		}
		else if (_isClicked)
		{
			clickObject();
			_isClicked = false;
		}
		else
		{
			team = searchObject();
		}

		switch (team)
		{
		case TEAM_NONE:
			_cursorState = CURSORSTATE_IDLE;
			break;
		case TEAM_NEUTRAL:
			break;
		case TEAM_MYTEAM:
			_cursorState = CURSORSTATE_ON_ME;
			break;
		case TEAM_FRIEND:
			break;
		case TEAM_ENEMY:
			break;
		}

		if (_selectInfo.isSelected && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			switch (_cursorState)
			{
			case CURSORSTATE_IDLE:
				if (_selectInfo.isBuilding)
				{

				}
				else
				{
					for (int i = 0; i < _selectInfo.unitNum; i++)
					{
						_selectInfo.unit[i]->receiveCommand(COMMAND_MOVE, ptMouseReal);
					}
				}
				break;
			case CURSORSTATE_FOCUS_TO_ME:
				break;
			case CURSORSTATE_FOCUS_TO_NEUTRAL:
				break;
			case CURSORSTATE_FOCUS_TO_ENEMY:
				break;
			case CURSORSTATE_ON_ME:
				break;
			case CURSORSTATE_ON_NEUTRAL:
				break;
			case CURSORSTATE_ON_ENEMY:
				break;
			case CURSORSTATE_DRAGING:
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
			}
		}

	}
}

BOOL gameController::actionHotkeys(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		MAINCAMERA->moveCamera(DIRECTION_RG);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		MAINCAMERA->moveCamera(DIRECTION_LF);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		MAINCAMERA->moveCamera(DIRECTION_UP);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		MAINCAMERA->moveCamera(DIRECTION_DN);
	}

	//hotkey 누르면

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
		case CURSORSTATE_IDLE:
			_imgCursor = IMAGEMANAGER->findImage(L"cursor-Idle");
			break;
		case CURSORSTATE_FOCUS_TO_ME:
			break;
		case CURSORSTATE_FOCUS_TO_NEUTRAL:
			break;
		case CURSORSTATE_FOCUS_TO_ENEMY:
			break;
		case CURSORSTATE_ON_ME:
			_imgCursor = IMAGEMANAGER->findImage(L"cursor-onme");
			break;
		case CURSORSTATE_ON_NEUTRAL:
			_imgCursor = IMAGEMANAGER->findImage(L"cursor-onneutral");
			break;
		case CURSORSTATE_ON_ENEMY:
			_imgCursor = IMAGEMANAGER->findImage(L"cursor-onenemy");
			break;
		case CURSORSTATE_DRAGING:
			_imgCursor = IMAGEMANAGER->findImage(L"cursor-Dragging");
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
}

void gameController::renderCursor(void)
{
	if (_isInInterface)
	{
		_imgCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
	}
	else
	{
		switch (_cursorState)
		{
		case CURSORSTATE_IDLE:
			_imgCursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			break;
		case CURSORSTATE_FOCUS_TO_ME:
			break;
		case CURSORSTATE_FOCUS_TO_NEUTRAL:
			break;
		case CURSORSTATE_FOCUS_TO_ENEMY:
			break;
		case CURSORSTATE_ON_ME:
			_imgCursor->frameRenderCT(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			break;
		case CURSORSTATE_ON_NEUTRAL:
			_imgCursor->frameRenderCT(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			break;
		case CURSORSTATE_ON_ENEMY:
			_imgCursor->frameRenderCT(getMemDC(), _ptMouse.x, _ptMouse.y, _frameCursor, 0);
			break;
		case CURSORSTATE_DRAGING:
			_imgCursor->renderCT(getMemDC(), _ptMouse.x, _ptMouse.y);
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
		}
	}
}

void gameController::renderInterface(void)
{
	if (_imgInterface == NULL)
		return;

	_imgInterface->render(getMemDC());

	if (_selectInfo.isBuilding)
	{
		if (_selectInfo.building == NULL) return;
		//_selectInfo.building->render();
	}
	else
	{
		if (_selectInfo.unitNum == 0)
		{
			return;
		}
		else if (_selectInfo.unitNum == 1)
		{
			tagUnitBaseStatus baseStatus = _selectInfo.unit[0]->getBaseStatus();
			tagUnitBattleStatus battleStatus = _selectInfo.unit[0]->getBattleStatus();

			if (battleStatus.isDead)
			{
				_selectInfo.unit[0] = NULL;
			}
			else
			{
				COLORREF oldColor = GetTextColor(getMemDC());

				//이미지
				baseStatus.imgStat1->render(getMemDC(), 172, 396);

				//HP
				RECT rcHP = RectMake(178, 453, 43, 12);
				TCHAR strHP[100];
				_stprintf(strHP, L"%d / %d", (INT)battleStatus.curHP, (INT)battleStatus.maxHP);

				SetTextColor(getMemDC(), TEXTCOLOR_UNITHP);
				DrawText(getMemDC(), strHP, _tcslen(strHP), &rcHP, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				if (baseStatus.useMP)
				{
					//MP
					RECT rcMP = RectMake(178, 470, 43, 12);
					TCHAR strMP[100];
					_stprintf(strMP, L"%d / %d", (INT)battleStatus.curMP, (INT)battleStatus.maxMP);
					SetTextColor(getMemDC(), TEXTCOLOR_UNITMP);
					DrawText(getMemDC(), strMP, _tcslen(strMP), &rcMP, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}


				SetTextColor(getMemDC(), oldColor);
			}
		}
		else
		{
			for (int i = 0; i < _selectInfo.unitNum; i++)
			{
				if (_selectInfo.unit[i] == NULL) continue;
			}
		}
	}
}

void gameController::renderCommands(void)
{
	for (int i = 0; i < COMMAND_MAX; i++)
	{
		if (_unitCommandInfo.img[i] == NULL) continue;

		_unitCommandInfo.img[i]->render(getMemDC(), _unitCommandInfo.rc[i].left, _unitCommandInfo.rc[i].top);
	}
}

TEAM gameController::searchObject(void)
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
					return TEAM_MYTEAM;
				}
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
					_selectInfo.isBuilding = false;
					_selectInfo.unitNum = 1;
					_selectInfo.unit[0] = vUnitsInCamera[j];
					_selectInfo.building = NULL;

					_unitCommandInfo.curCommand = _selectInfo.unit[0]->getBattleStatus().curCommand;
					memcpy(_unitCommandInfo.commands, _selectInfo.unit[0]->getBaseStatus().commands, sizeof(DWORD)*COMMAND_MAX);
					//for (int c = 0; c < COMMAND_MAX; c++)
					//{
					//	_commandSet[c].command = vUnitsInCamera[j]->getBaseStatus().commands[c];
					//}

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
	rcDrag.top    += MAINCAMERA->getCameraY();
	rcDrag.right  += MAINCAMERA->getCameraX();
	rcDrag.bottom += MAINCAMERA->getCameraY();

	RECT temp;

	int unitNum = 0;
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
					_selectInfo.isBuilding = false;
					//_selectInfo.unitNum = 1;
					_selectInfo.unit[unitNum] = vUnitsInCamera[j];
					_selectInfo.building = NULL;



					_unitCommandInfo.curCommand = _selectInfo.unit[unitNum]->getBattleStatus().curCommand;
					memcpy(_unitCommandInfo.commands, _selectInfo.unit[unitNum]->getBaseStatus().commands, sizeof(DWORD)*COMMAND_MAX);
					//for (int c = 0; c < COMMAND_MAX; c++)
					//{
					//	_commandSet[c].command = vUnitsInCamera[j]->getBaseStatus().commands[c];
					//}

					unitNum++;

					if (unitNum == 12) break;
				}
			}
		}

		if (unitNum > 0)
		{
			_selectInfo.unitNum = unitNum;
			return TEAM_MYTEAM;
		}


	}

	return TEAM_NONE;

}

void gameController::setCommandSet(void)
{
	if (_selectInfo.isSelected == FALSE)
		return;


	TCHAR strKey[100] = L"";

	for (int i = 0; i < COMMAND_MAX; i++)
	{
		int same = 0;

		if (_selectInfo.isBuilding)
		{
			//_unitCommandInfo.curCommand = _selectInfo.building->getBattleStatus().curCommand;
		}
		else
		{
			_unitCommandInfo.curCommand = _selectInfo.unit[0]->getBattleStatus().curCommand;
		}

		if (_unitCommandInfo.curCommand == _unitCommandInfo.commands[i])	same = 1;

		switch (_unitCommandInfo.commands[i])
		{
		case COMMAND_NONE:				_unitCommandInfo.img[i] = NULL;			break;
		case COMMAND_MOVE:				_stprintf(strKey, L"command-move%d", same);			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_STOP:				_stprintf(strKey, L"command-stop%d", same);			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_ATTACK:			_stprintf(strKey, L"command-attack%d", same);		_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_PATROL:			_stprintf(strKey, L"command-patrol%d", same);		_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_HOLD:				_stprintf(strKey, L"command-hold%d", same);			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_GATHER:			_stprintf(strKey, L"command-gather%d", same);		_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_RETURNCARGO:		_stprintf(strKey, L"command-return%d", same);		_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_BUILD1:			_stprintf(strKey, L"command-build0");				_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_BUILD2:			_stprintf(strKey, L"command-build1");				_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_BURROW:
		{
			if (_player[_playerNum]->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_EVOLVE_BURROW].complete == FALSE)	same = 2;
			_stprintf(strKey, L"command-burrow%d", same);
			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);
			break;
		}
		case COMMAND_UNBURROW:			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_LURKER:			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_INFEST:			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_BROODRING:			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_ENSNARE:			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_CONSUME:			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_DARKSWARM:			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		case COMMAND_PLAGUE:			_unitCommandInfo.img[i] = IMAGEMANAGER->findImage(strKey);			break;
		}
	}
}