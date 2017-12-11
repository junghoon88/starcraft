#include "stdafx.h"


#include "player.h"



player::player()
{
}


player::~player()
{

}

HRESULT player::init(PLAYER playerNum)
{
	_playerNum = playerNum;

	_isGaming = TRUE;

	_zergUpgrade = new zergUpgrade;

	drone = new zuDrone;
	drone->setLinkAdressZergUpgrade(_zergUpgrade);
	drone->init(playerNum, { 100, 100 });


	return S_OK;
}

void player::release(void)
{
	SAFE_DELETE(drone);

	SAFE_DELETE(_zergUpgrade);
}

void player::update(void) 
{
	drone->update();
}

void player::render(void) 
{
	drone->render();
}

void player::getChar(WPARAM wParam)
{

}

