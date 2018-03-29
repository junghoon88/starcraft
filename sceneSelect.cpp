#include "stdafx.h"
#include "sceneSelect.h"

#define TEXTCOLOR_NORMAL	RGB(76, 196, 40)
#define TEXTCOLOR_CLICKED	RGB(180, 252, 116)


#define FILENAME_STARTX		80
#define FILENAME_STARTY		80
#define FILENAME_WIDTH		200
#define FILENAME_HEIGHT		30

sceneSelect::sceneSelect()
{
	_level = SELECTLEVEL1;

	for (int i = 0; i < BTNMENU_MAX; i++)
	{
		_btn[i] = NULL;
	}

	_imgBackground1 = NULL;
	_imgBackground2 = NULL;
	_imgFade = NULL;

	_imgMapList = NULL;

	_fading = FADE_NONE;
	_fadeTime = 0.0f;
	_alpha = 0;
	_dir = 1;
}


sceneSelect::~sceneSelect()
{
}

HRESULT sceneSelect::init(void)
{
	_btn[BTNMENU_GAMESELECT] = new button;
	_btn[BTNMENU_GAMESELECT]->init(L"버튼2", L"게임선택",		WINSIZEX - 100, WINSIZEY - 200, { 0,0 }, { 0,0 }, cbFuncGameSelect, this);
	_btn[BTNMENU_GAMESELECT]->setColor(RGB(92, 237, 48));
	_btn[BTNMENU_MAPTOOL] = new button;
	_btn[BTNMENU_MAPTOOL]->init(L"버튼2", L"맵에디터",		WINSIZEX - 100, WINSIZEY - 150, { 0,0 }, { 0,0 }, cbFuncMaptool, this);
	_btn[BTNMENU_MAPTOOL]->setColor(RGB(92, 237, 48));
	_btn[BTNMENU_EXIT] = new button;
	_btn[BTNMENU_EXIT]->init(L"버튼2", L"나가기",			WINSIZEX - 100, WINSIZEY - 100, { 0,0 }, { 0,0 }, cbFuncGameExit, this);
	_btn[BTNMENU_EXIT]->setColor(RGB(92, 237, 48));
	_btn[BTNMENU_START] = new button;
	_btn[BTNMENU_START]->init(L"버튼2", L"게임시작",			WINSIZEX - 100, WINSIZEY - 150, { 0,0 }, { 0,0 }, cbFuncStart, this);
	_btn[BTNMENU_START]->setColor(RGB(92, 237, 48));
	_btn[BTNMENU_BACK] = new button;
	_btn[BTNMENU_BACK]->init(L"버튼2", L"뒤로가기",			WINSIZEX - 100, WINSIZEY - 100, { 0,0 }, { 0,0 }, cbFuncBack, this);
	_btn[BTNMENU_BACK]->setColor(RGB(92, 237, 48));

	_imgBackground1 = IMAGEMANAGER->findImage(L"background1");
	_imgBackground2 = IMAGEMANAGER->findImage(L"background2");
	_imgFade = IMAGEMANAGER->findImage(L"fade");

	_imgMapList = IMAGEMANAGER->findImage(L"window1");
	_rcMapList = RectMake(FILENAME_STARTX - 20, FILENAME_STARTY, FILENAME_WIDTH + 40, FILENAME_HEIGHT * 8);

	return S_OK;
}


void sceneSelect::release(void)
{
	for (int i = 0; i < BTNMENU_MAX; i++)
	{
		SAFE_DELETE(_btn[i]);
	}
}

void sceneSelect::update(void)
{
	float tick = TIMEMANAGER->getElapsedTime();

	if (_fading != FADE_NONE)
	{
		_fadeTime += tick;
		if (_fadeTime >= (1.0f / 30))
		{
			_fadeTime -= (1.0f / 30);

			_alpha += 0x11 * _dir;
			if (_alpha == 0xff)
			{
				_dir = -1;

				if (_fading == FADE_TO_LEVEL1)
				{
					_level = SELECTLEVEL1;
				}
				else if (_fading == FADE_TO_LEVEL2)
				{
					_level = SELECTLEVEL2;
				}
			}
			if (_alpha == 0 && _dir == -1)
			{
				_dir = 1;
				_fadeTime = 0.0f;
				_fading = FADE_NONE;
			}
		}
		return;
	}
	

	if (_level == SELECTLEVEL1)
	{
		for (int i = 0; i <= BTNMENU_EXIT; i++)
		{
			_btn[i]->update();
		}
	}
	else
	{
		if (_vMapFileInfo.size() > 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				int index = findSelectIndex();
				if (index > 0)
				{
					_vMapFileInfo[index].clicked = false;
					_vMapFileInfo[index-1].clicked = true;
				}
			}
			else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				int index = findSelectIndex();
				if (index < _vMapFileInfo.size() - 1)
				{
					_vMapFileInfo[index].clicked = false;
					_vMapFileInfo[index + 1].clicked = true;
				}
			}
		}


		for (int i = BTNMENU_START; i <= BTNMENU_BACK; i++)
		{
			_btn[i]->update();
		}
	}

}

void sceneSelect::render(void)
{
	if (_level == SELECTLEVEL1)
	{
		_imgBackground1->render(getMemDC());

		for (int i = 0; i <= BTNMENU_EXIT; i++)
		{
			_btn[i]->render();
		}
	}
	else
	{
		_imgBackground2->render(getMemDC());

		_imgMapList->render(getMemDC(), _rcMapList.left, _rcMapList.top);

		COLORREF oldColor = GetTextColor(getMemDC());

		for (int i = 0; i < _vMapFileInfo.size(); i++)
		{
			//RectangleMake(getMemDC(), _vMapFileInfo[i].rc);
			
			if (_vMapFileInfo[i].clicked)
			{
				SetTextColor(getMemDC(), TEXTCOLOR_CLICKED);
			}
			else
			{
				SetTextColor(getMemDC(), TEXTCOLOR_NORMAL);
			}

			DrawText(getMemDC(), _vMapFileInfo[i].str, _tcslen(_vMapFileInfo[i].str), &_vMapFileInfo[i].rc, DT_VCENTER | DT_SINGLELINE);
		}

		SetTextColor(getMemDC(), oldColor);


		for (int i = BTNMENU_START; i <= BTNMENU_BACK; i++)
		{
			_btn[i]->render();
		}
	}

	if (_fading != FADE_NONE)
	{
		_imgFade->alphaRender(getMemDC(), _alpha);
	}
		
}

//callback functions
void sceneSelect::cbFuncGameSelect(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->goNextLevel();
	ss->loadMapFiles();
}
void sceneSelect::cbFuncMaptool(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->setChangeScene(true, L"맵툴씬");
}
void sceneSelect::cbFuncGameExit(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	PostQuitMessage(0);
}
void sceneSelect::cbFuncStart(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->gameStart();
}
void sceneSelect::cbFuncBack(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->goPrevLevel();
}

void sceneSelect::gameStart(void)
{
	if (_vMapFileInfo.size() == 0)
		return;

	int index = findSelectIndex();


	TCHAR strFilename[100] = L"MapData/";
	_tcscat(strFilename, _vMapFileInfo[index].str);

	DATABASE->setMapFile(strFilename);
	

	setChangeScene(true, L"전투씬");

}


void sceneSelect::loadMapFiles(void)
{
	_vMapFileInfo.clear();

	int filenum = 0;
	//모든 파일 스캔 test
	WIN32_FIND_DATA wfd;
	HANDLE handle = FindFirstFile(L"MapData/*.map", &wfd);

	// 찾는 파일이 있다면,
	while (handle != INVALID_HANDLE_VALUE)
	{
		tagMapFileInfo temp;
		ZeroMemory(&temp, sizeof(tagMapFileInfo));
		_tcscpy(temp.str, wfd.cFileName);
		temp.rc = RectMake(FILENAME_STARTX, FILENAME_STARTY + FILENAME_HEIGHT * filenum + 10, FILENAME_WIDTH, FILENAME_HEIGHT);
		temp.clicked = false;
		_vMapFileInfo.push_back(temp);
		filenum++;

		// FindNextFile 리턴 값으로 다음값이 있을 경우 TRUE
		// 없을 경우 FALSE 값 리턴
		if (!FindNextFile(handle, &wfd))
		{
			break;
		}
	}
	// 파일 찾기 핸들 값 닫기   
	FindClose(handle);


	if (_vMapFileInfo.size() > 0)
	{
		_vMapFileInfo[0].clicked = true;
	}
}

int sceneSelect::findSelectIndex(void)
{
	if (_vMapFileInfo.size() > 0)
	{
		for (int i = 0; i < _vMapFileInfo.size(); i++)
		{
			if (_vMapFileInfo[i].clicked)
				return i;
		}
	}

	return -1;
}
