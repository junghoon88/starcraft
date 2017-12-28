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

	_playTime = 0.0f;


}


sceneBattle::~sceneBattle()
{
}


HRESULT sceneBattle::init(void)
{
	_gameMap = new gameMap;
	_gameMap->init();

	//게임오브젝트 최대 1000개로 잡는다.
	//_gameObjectPool = new gameObjectPool;
	//_gameObjectPool->init(1000);

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		RACES selectRaces = DATABASE->getSelectRaces((PLAYER)i);

		_player[i] = new player;
		_player[i]->setLinkAdressGamemap(_gameMap);
		//_player[i]->setLinkAdressGameObjectPool(_gameObjectPool);
		_player[i]->init((PLAYER)i, selectRaces);

		//_gameInterface[i] = new gameInterface;
		//_gameInterface[i]->init(selectRaces);
	}

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i]->getGameController()->setLinkAdressPlayers(_player[i], (PLAYER)i);
	}

	_selectPlayerNum = PLAYER1;

	ShowCursor(false);

	_zergProductionInfo = new zergProductionInfo(true);


	return S_OK;
}

void sceneBattle::release(void)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		SAFE_RELEASEDELETE(_player[i]);
		//SAFE_RELEASEDELETE(_gameInterface[i]);
	}

	SAFE_RELEASEDELETE(_gameMap);

	SAFE_DELETE(_zergProductionInfo);

	ShowCursor(true);
}

void sceneBattle::update(void)
{
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
	//_gameInterface[_selectPlayerNum]->update();
	_player[_selectPlayerNum]->getGameController()->update();



	//RENDERMANAGER->insertRectangle(ZORDER_GAMEOBJECT, RectMake(0, 0, 200, 200), PENVERSION_BLUE2);
	//RENDERMANAGER->insertRectangle(ZORDER_GAMEOBJECT, RectMake(200, 200, 200, 200), PENVERSION_MOUSEDRAG);
	//RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, RectMake(100, 100, 200, 200), PENVERSION_UNITCLICK);

	RENDERMANAGER->sort();
}

void sceneBattle::render(void)
{
	_gameMap->render();


	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i]->render(_player[_selectPlayerNum]->getFog());
	}


	_player[_selectPlayerNum]->getGameController()->render();

	RENDERMANAGER->render(getMemDC());
}

void sceneBattle::getChar(WPARAM wParam)
{
	_player[_selectPlayerNum]->getGameController()->getChar(wParam);
}
