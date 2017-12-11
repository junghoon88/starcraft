#include "stdafx.h"
#include "sceneBattle.h"


sceneBattle::sceneBattle()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i] = NULL;
	}
}


sceneBattle::~sceneBattle()
{
}


HRESULT sceneBattle::init(void)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i] = new player;
		_player[i]->init((PLAYER)i);
	}

	_selectPlayerNum = PLAYER1;

	return S_OK;
}

void sceneBattle::release(void)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		SAFE_RELEASE(_player[i]);
		SAFE_DELETE(_player[i]);
	}
}

void sceneBattle::update(void)
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_player[i]->update();
	}
}

void sceneBattle::render(void)
{
	_player[_selectPlayerNum]->render();
}

void sceneBattle::getChar(WPARAM wParam)
{

}
