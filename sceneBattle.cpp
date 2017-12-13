#include "stdafx.h"
#include "sceneBattle.h"


sceneBattle::sceneBattle()
	: _gameController(NULL)
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

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		RACES selectRaces = DATABASE->getSelectRaces((PLAYER)i);

		_player[i] = new player;
		_player[i]->setLinkAdressGamemap(_gameMap);
		_player[i]->init((PLAYER)i, selectRaces);

		//_gameInterface[i] = new gameInterface;
		//_gameInterface[i]->init(selectRaces);
	}

	_selectPlayerNum = PLAYER1;


	_gameController = new gameController;
	_gameController->init(_selectPlayerNum, _player[_selectPlayerNum]->getRaces());
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_gameController->setLinkAdressPlayers(_player[i], (PLAYER)i);
	}
	//_gameController->setLinkAdressGameInterface(_gameInterface[_selectPlayerNum]);


	ShowCursor(false);

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

	SAFE_RELEASEDELETE(_gameController);

	ShowCursor(true);
}

void sceneBattle::update(void)
{
	_gameMap->update();
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i]->update();
	}
	//_gameInterface[_selectPlayerNum]->update();
	_gameController->update();
}

void sceneBattle::render(void)
{
	_gameMap->render();
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i]->render(_player[_selectPlayerNum]->getFog());
	}
	//_gameInterface[_selectPlayerNum]->render();
	_gameController->render();
}

void sceneBattle::getChar(WPARAM wParam)
{

}
