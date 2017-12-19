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



		tagUnitBattleStatus battleStatus = units[num]->getBattleStatus();

		//AStar �� ������� ������ ����
		if (battleStatus.useAstar == FALSE)
			continue;

		//AStar �� ����ϴµ� ����� �������� ����
		if (battleStatus.calcAstar == TRUE)
			continue;

		units[num]->setIsBusy(TRUE);

		POINT ptStartTile, ptEndTile;
		ptStartTile.x = battleStatus.pt.toPoint().x / GAMEMAP_TILESIZE;
		ptStartTile.y = battleStatus.pt.toPoint().y / GAMEMAP_TILESIZE;
		ptEndTile.x = battleStatus.ptTarget.x / GAMEMAP_TILESIZE;
		ptEndTile.y = battleStatus.ptTarget.y / GAMEMAP_TILESIZE;


		p->getAstar()->clearTiles();
		p->getAstar()->setTiles(ptStartTile, ptEndTile);
		p->getAstar()->pathFinder(p->getAstar()->getStartTile());
		units[num]->setVCloseList(p->getAstar()->getCloseList());

		units[num]->setCalcAstar(TRUE);
		units[num]->setIsBusy(FALSE);
	}

	return 0;
}

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

player::player()
	: _zergUpgrade(NULL), _gameMap(NULL), _fog(NULL), _aStar(NULL), _gameController(NULL)
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

	_gameController = new gameController;
	_gameController->init(playerNum, _races);
	_gameController->setLinkAdressMyPlayer(this);


	unsigned int threadId = 0;
	_hAstarThread = (HANDLE)_beginthreadex(NULL, 0, &AstarThread, this, 0, &threadId);
	//_hControllerThread = (HANDLE)_beginthreadex(NULL, 0, &ControllerThread, this, 0, &threadId);
	_endThread = FALSE;

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
	for (UINT i = 0; i < _vUnits.size(); i++)
	{
		_vUnits[i]->update();
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

	//_fog->render();
}


void player::checkInCamera(void)
{
	_vBuildingsInCamera.clear();	//ī�޶� �����ִ� �ǹ���
	_vUnitsInCamera.clear();		//ī�޶� �����ִ� ���ֵ�

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

bool player::haveBuilding(BUILDINGNUM_ZERG num)
{
	for (UINT i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->getBuildingNumZerg() == num)
		{
			//(�״� �ִϸ��̼��� ����) �׾����� üũ�ϴ°� ���߿� �ʿ�������? 
			return true;
		}
	}


	return false;
}