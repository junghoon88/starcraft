#include "stdafx.h"


#include "player.h"



player::player()
	: _zergUpgrade(NULL), _gameMap(NULL), _fog(NULL), _aStar(NULL)
{
}


player::~player()
{

}

HRESULT player::init(PLAYER playerNum, RACES races)
{
	_playerNum = playerNum;
	_races = races;

	_isGaming = TRUE;

	_zergUpgrade = new zergUpgrade;

	_fog = new fog;
	_fog->init();

	_aStar = new aStar;
	_aStar->setLinkAdressGameMap(_gameMap);
	_aStar->init();


	//debug
	zuDrone* drone = new zuDrone;
	drone->setLinkAdressZergUpgrade(_zergUpgrade);
	drone->setLinkAdressAstar(_aStar);
	drone->init(playerNum, { 200, 200 });
	_vUnits.push_back(drone);




	return S_OK;
}

void player::release(void)
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		SAFE_RELEASEDELETE(_vUnits[i]);
	}
	_vUnits.clear();


	SAFE_RELEASEDELETE(_fog);

	SAFE_DELETE(_zergUpgrade);
}

void player::update(void) 
{
	for (int i = 0; i < _vUnits.size(); i++)
	{
		_vUnits[i]->update();
	}

	checkInCamera();

	_fog->update();
}

void player::render(fog* fog)
{
	for (int i = 0; i < _vUnitsInCamera.size(); i++)
	{
		_vUnitsInCamera[i]->render();
	}

	//_fog->render();
}


void player::checkInCamera(void)
{
	_vBuildingsInCamera.clear();	//카메라에 보여주는 건물들
	_vUnitsInCamera.clear();		//카메라에 보여주는 유닛들

	RECT temp;
	RECT rcCamera = MAINCAMERA->getRectCamera();

	for (int i = 0; i < _vUnits.size(); i++)
	{
		RECT rcBody = _vUnits[i]->getBattleStatus().rcBody;
		if (IntersectRect(&temp, &rcCamera, &rcBody))
		{
			_vUnitsInCamera.push_back(_vUnits[i]);
		}
	}
}

