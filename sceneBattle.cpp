#include "stdafx.h"
#include "sceneBattle.h"



sceneBattle::sceneBattle()
	: _gameMap(NULL), _zergProductionInfo(NULL)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i] = NULL;
		//_gameInterface[i] = NULL;
	}



}


sceneBattle::~sceneBattle()
{
}


HRESULT sceneBattle::init(void)
{
	_gameMap = new gameMap;
	_gameMap->init();


	_zergProductionInfo = new zergProductionInfo(true);

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		RACES selectRaces = DATABASE->getSelectRaces((PLAYER)i);

		_player[i] = new player;
		_player[i]->setLinkAdressGamemap(_gameMap);
		_player[i]->setLinkAdressZergProduction(_zergProductionInfo);
		_player[i]->init((PLAYER)i, selectRaces);

		//_gameInterface[i] = new gameInterface;
		//_gameInterface[i]->init(selectRaces);
	}

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i]->getGameController()->setLinkAdressPlayers(_player[i], (PLAYER)i);
		_player[i]->getGameController()->getGameInterface()->setLinkAdressPlayers(_player[i], (PLAYER)i);
		_player[i]->getGameController()->getMiniMap()->setLinkAdressPlayers(_player[i], (PLAYER)i);
	}

	_selectPlayerNum = PLAYER1;

	ShowCursor(false);

	initEffects();

	SOUNDMANAGER->stop(L"StarCraft-OST");
	SOUNDMANAGER->play(L"Zerg_theme_1");



	_playTime = 0.0f;

	return S_OK;
}

void sceneBattle::release(void)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		SAFE_RELEASEDELETE(_player[i]);
		//SAFE_RELEASEDELETE(_gameInterface[i]);
	}

	SAFE_DELETE(_zergProductionInfo);

	SAFE_RELEASEDELETE(_gameMap);

	EFFECTMANAGER->release();

	ShowCursor(true);
}

void sceneBattle::update(void)
{
	DWORD tick1 = GetTickCount();


	_playTime += TIMEMANAGER->getElapsedTime();


	//카메라 이동은 여기(게임컨트롤러에서 하지 않고)
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




	_gameMap->update();


	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i]->update();
	}

	DWORD tick2 = GetTickCount();

	_player[_selectPlayerNum]->getGameController()->update();

	DWORD tick3 = GetTickCount();


	//RENDERMANAGER->insertRectangle(ZORDER_GAMEOBJECT, RectMake(0, 0, 200, 200), PENVERSION_BLUE2);
	//RENDERMANAGER->insertRectangle(ZORDER_GAMEOBJECT, RectMake(200, 200, 200, 200), PENVERSION_MOUSEDRAG);
	//RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, RectMake(100, 100, 200, 200), PENVERSION_UNITCLICK);

	RENDERMANAGER->sort();

	DWORD tick4 = GetTickCount();

	EFFECTMANAGER->update();

	printf("");

}

void sceneBattle::render(void)
{
	_gameMap->render();


	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i]->render(_player[_selectPlayerNum]->getFog());
	}


	_player[_selectPlayerNum]->getGameController()->render();


	//play time
	{
		TCHAR time[20];
		int min = (int)_playTime / 60;
		int sec = (int)_playTime % 60;
		_stprintf(time, L"%02d:%02d", min, sec);

		RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(324, 362, 52, 12), time, TIMECOLOR);
	}


	RENDERMANAGER->render(getMemDC());

	EFFECTMANAGER->render();
}

void sceneBattle::getChar(WPARAM wParam)
{
	_player[_selectPlayerNum]->getGameController()->getChar(wParam);
}



void sceneBattle::initEffects(void)
{
	EFFECTMANAGER->addEffect(L"마우스우클릭", L"cursor-FocusToMe", ZORDER_GAMEMOUSEDRAG, 15, 0.016f, 10);


	//Unit
	EFFECTMANAGER->addEffect(L"ZU-larva-Death",			L"ZU-larva-Death"		, ZORDER_GAMEOBJECT, 15, 0.016f, 200);		
	EFFECTMANAGER->addEffect(L"ZU-zergegg-Death",		L"ZU-zergegg-Death"		, ZORDER_GAMEOBJECT, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-drone-Death",			L"ZU-drone-Death"		, ZORDER_GAMEOBJECT, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-zergling-Death",		L"ZU-zergling-Death"	, ZORDER_GAMEOBJECT, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Death",		L"ZU-hydralisk-Death"	, ZORDER_GAMEOBJECT, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-lurker-Death",		L"ZU-lurker-Death"		, ZORDER_GAMEOBJECT, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-lurkeregg-Death",		L"ZU-lurkeregg-Death"	, ZORDER_GAMEOBJECT, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-ultralisk-Death",		L"ZU-ultralisk-Death"	, ZORDER_GAMEOBJECT, 15, 0.016f, 200);
	//EFFECTMANAGER->addEffect(L"ZU-broodling-Death"
	EFFECTMANAGER->addEffect(L"ZU-defiler-Death",		L"ZU-defiler-Death"		, ZORDER_GAMEOBJECT, 15, 0.016f, 200);
	//infestedterran
	EFFECTMANAGER->addEffect(L"ZU-overlord-Death",		L"ZU-overlord-Death"	, ZORDER_GAMEOBJECTAIR, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-mutalisk-Death",		L"ZU-mutalisk-Death"	, ZORDER_GAMEOBJECTAIR, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-scourge-Death",		L"ZU-scourge-Death"		, ZORDER_GAMEOBJECTAIR, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-queen-Death",			L"ZU-queen-Death"		, ZORDER_GAMEOBJECTAIR, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-cocoon-Death",		L"ZU-cocoon-Death"		, ZORDER_GAMEOBJECTAIR, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-guadian-Death",		L"ZU-guadian-Death"		, ZORDER_GAMEOBJECTAIR, 15, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-devourer-Death",		L"ZU-devourer-Death"	, ZORDER_GAMEOBJECTAIR, 15, 0.016f, 200);

	//Bullet
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Bullet000", L"ZU-hydralisk-Bullet000", ZORDER_GAMEOBJECT, 30, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Bullet045", L"ZU-hydralisk-Bullet045", ZORDER_GAMEOBJECT, 30, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Bullet090", L"ZU-hydralisk-Bullet090", ZORDER_GAMEOBJECT, 30, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Bullet135", L"ZU-hydralisk-Bullet135", ZORDER_GAMEOBJECT, 30, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Bullet180", L"ZU-hydralisk-Bullet180", ZORDER_GAMEOBJECT, 30, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Bullet225", L"ZU-hydralisk-Bullet225", ZORDER_GAMEOBJECT, 30, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Bullet270", L"ZU-hydralisk-Bullet270", ZORDER_GAMEOBJECT, 30, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-hydralisk-Bullet315", L"ZU-hydralisk-Bullet315", ZORDER_GAMEOBJECT, 30, 0.016f, 200);


	EFFECTMANAGER->addEffect(L"ZU-mutalisk-BulletEffect",	L"ZU-mutalisk-BulletEffect", ZORDER_GAMEOBJECTAIR, 30, 0.016f, 200);
	EFFECTMANAGER->addEffect(L"ZU-guadian-BulletEffect",	L"ZU-guadian-BulletEffect",  ZORDER_GAMEOBJECTAIR, 30, 0.016f, 200);

	//Building

}
