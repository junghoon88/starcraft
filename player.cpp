#include "stdafx.h"
#include "player.h"

#include <process.h>

unsigned CALLBACK AstarThread(void* pArguments)
{
	UINT num = 0;

	player* p = (player*)pArguments;
	vUnits units = p->getUnits();

	while (1)
	{
		Sleep(10);

		if (p->getEndThread())
		{
			break;
		}

		if (p->getAstar() == NULL)
			continue;

		if (units.size() == 0)
			continue;

		if (++num >= units.size()) 
			num = 0;



		tagBattleStatus battleStatus = units[num]->getBattleStatus();

		//AStar 를 사용하지 않으면 다음
		if (battleStatus.useAstar == FALSE)
			continue;

		//AStar 를 사용하는데 계산을 끝냈으면 다음
		if (battleStatus.calcAstar == TRUE)
			continue;

		units[num]->setIsBusy(TRUE);

		POINT ptStartTile, ptEndTile;
		ptStartTile.x = battleStatus.pt.toPoint().x / TILESIZE;
		ptStartTile.y = battleStatus.pt.toPoint().y / TILESIZE;
		ptEndTile.x = battleStatus.ptTarget.x / TILESIZE;
		ptEndTile.y = battleStatus.ptTarget.y / TILESIZE;


		p->getAstar()->clearTiles();
		p->getAstar()->setTiles(ptStartTile, ptEndTile);
		p->getAstar()->pathFinder(p->getAstar()->getStartTile());
		units[num]->setVCloseList(p->getAstar()->getCloseList());

		units[num]->setCalcAstar(TRUE);
		units[num]->setIsBusy(FALSE);
	}

	return 0;
}

#if 0
unsigned CALLBACK ControllerThread(void* pArguments)
{
	player* p = (player*)pArguments;
	vUnits units = p->getUnits();

	while (1)
	{
		Sleep(10);

		if (p->getEndThread())
		{
			break;
		}


		if (p->getGameController() == NULL)
			continue;

		p->getGameController()->update();
		//p->getGameController()->render();

	}
	return 0;
}
#endif

player::player()
	: _zergUpgrade(NULL), _gameMap(NULL), _fog(NULL), _aStar(NULL), _gameController(NULL)//, _gameObjectPool(NULL)
{
}


player::~player()
{

}

HRESULT player::init(PLAYER playerNum, RACES races)
{
	_myMineral = 5000;
	_myGas = 1000;
	_myControl = _myControlMax = 0;

	_playerNum = playerNum;
	_races = races;

	_isGaming = TRUE;

	_zergUpgrade = new zergUpgrade;

	_fog = new fog;
	_fog->init();

	_aStar = new aStar;
	_aStar->setLinkAdressGameMap(_gameMap);
	_aStar->init();

	_gameController = new gameController;
	_gameController->init(playerNum, _races);
	_gameController->setLinkAdressMyPlayer(this);
	_gameController->setLinkAdressGameMap(_gameMap);


	unsigned int threadId = 0;
	_hAstarThread = (HANDLE)_beginthreadex(NULL, 0, &AstarThread, this, 0, &threadId);
	//_hControllerThread = (HANDLE)_beginthreadex(NULL, 0, &ControllerThread, this, 0, &threadId);
	_endThread = FALSE;



	//debug
	zuDrone* drone = new zuDrone(_playerNum);
	drone->setLinkAdressZergUpgrade(_zergUpgrade);
	drone->setLinkAdressAstar(_aStar);
	drone->setLinkAdressPlayer(this);
	drone->init({ 200, 200 });
	_vUnits.push_back(drone);



	return S_OK;
}

void player::release(void)
{
	_endThread = TRUE;

	WaitForSingleObject(_hAstarThread, INFINITE);
	CloseHandle(_hAstarThread);

	//WaitForSingleObject(_hControllerThread, INFINITE);
	//CloseHandle(_hControllerThread);



	for (UINT i = 0; i < _vUnits.size(); i++)
	{
		while (_vUnits[i]->getIsBusy() == true)
		{
			Sleep(1);
		}
		SAFE_RELEASEDELETE(_vUnits[i]);
	}
	_vUnits.clear();


	SAFE_RELEASEDELETE(_fog);

	SAFE_RELEASEDELETE(_aStar);
	SAFE_RELEASEDELETE(_gameController);


	SAFE_DELETE(_zergUpgrade);
}

void player::update(void) 
{
	checkUnitValid();
	checkBuildingVaild();

	for (UINT i = 0; i < _vUnits.size(); i++)
	{
		_vUnits[i]->update();
	}

	for (UINT i = 0; i < _vBuildings.size(); i++)
	{
		_vBuildings[i]->update();
	}


	checkInCamera();

	_fog->update();
}

void player::render(fog* fog)
{
	for (UINT i = 0; i < _vUnitsInCamera.size(); i++)
	{
		_vUnitsInCamera[i]->render();
	}
	for (UINT i = 0; i < _vBuildings.size(); i++)
	{
		_vBuildings[i]->render();
	}

	//_fog->render();
}


void player::checkInCamera(void)
{
	_vBuildingsInCamera.clear();	//카메라에 보여주는 건물들
	_vUnitsInCamera.clear();		//카메라에 보여주는 유닛들

	RECT temp;
	RECT rcCamera = MAINCAMERA->getRectCamera();

	for (UINT i = 0; i < _vUnits.size(); i++)
	{
		RECT rcBody = _vUnits[i]->getBattleStatus().rcBody;
		if (IntersectRect(&temp, &rcCamera, &rcBody))
		{
			_vUnitsInCamera.push_back(_vUnits[i]);
		}
	}
}

bool player::isHaveBuilding(BUILDINGNUM_ZERG num)
{
	for (UINT i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->getBuildingNumZerg() == num)
		{
			//(죽는 애니메이션이 길경우) 죽었는지 체크하는것 나중에 필요할지도? 
			return true;
		}
	}


	return false;
}

bool player::useResource(UINT mineral, UINT gas)
{
	if (_myMineral >= mineral && _myGas >= gas)
	{
		_myMineral -= mineral;
		_myGas -= gas;
		return true;
	}
	else
	{
		if (_myMineral < mineral)
		{
			//미네랄 부족
		}
		else if (_myGas < gas)
		{
			//가스 부족
		}
	}

	return false;
}

bool player::useResource(UINT mineral, UINT gas, float control)
{
	if (_myMineral >= mineral && _myGas >= gas && (_myControl + control) <= _myControlMax)
	{
		_myMineral -= mineral;
		_myGas -= gas;
		return true;
	}
	else
	{
		if (_myMineral < mineral)
		{
			//미네랄 부족
		}
		else if (_myGas < gas)
		{
			//가스 부족
		}
		else if ((_myControl + control) > _myControlMax)
		{
			//인구수 부족
		}
	}


	return false;
}



void player::checkUnitValid(void)
{
	for (int i = 0; i < _vUnits.size(); )
	{
		if (_vUnits[i]->getValid() == false)
		{
			_gameController->changeSelectInfoToNextObect(_vUnits[i]);
			_vUnits.erase(_vUnits.begin() + i);
		}
		else ++i;
	}
}
void player::checkBuildingVaild(void)
{
	for (int i = 0; i < _vBuildings.size(); )
	{
		if (_vBuildings[i]->getValid() == false)
		{
			_gameController->changeSelectInfoToNextObect(_vBuildings[i]);
			_vBuildings.erase(_vBuildings.begin() + i);
		}
		else ++i;
	}
}
