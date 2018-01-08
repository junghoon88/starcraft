#include "stdafx.h"
#include "player.h"

#include <process.h>

unsigned CALLBACK AstarThread(void* pArguments)
{
	UINT num = 0;

	player* p = (player*)pArguments;

	while (1)
	{
		Sleep(1);

		vUnits units = p->getUnits();


		if (p->getEndThread())
			break;

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

		if (units[num]->getIsBusy() != 0)
			continue;

		units[num]->addIsBusy(0x01);

		POINT ptStartTile, ptEndTile;
		ptStartTile.x = battleStatus.pt.toPoint().x / TILESIZE;
		ptStartTile.y = battleStatus.pt.toPoint().y / TILESIZE;
	
		if (battleStatus.targetObject == NULL)
		{
			ptEndTile.x = battleStatus.ptTarget.x / TILESIZE;
			ptEndTile.y = battleStatus.ptTarget.y / TILESIZE;
		}
		else
		{
			POINT ptTarget = battleStatus.targetObject->getBattleStatus().pt.toPoint();
			ptEndTile.x = ptTarget.x / TILESIZE;
			ptEndTile.y = ptTarget.y / TILESIZE;
		}
		


		p->getAstar()->clearTiles();
		p->getAstar()->updateMapInfo();
		p->getAstar()->setTiles(ptStartTile, ptEndTile);
		p->getAstar()->pathFinder(p->getAstar()->getStartTile());
		units[num]->setVCloseList(p->getAstar()->getCloseList());

		units[num]->setCalcAstar(TRUE);
		units[num]->deleteIsBusy(0x01);
	}

	return 0;
}

unsigned CALLBACK CreepThread(void* pArguments)
{
	player* p = (player*)pArguments;

	while (1)
	{
		Sleep(500);

		if (p->getEndThread())
		{
			break;
		}

		p->getCreepManager()->update();
		p->getGameController()->getMiniMap()->updateMiniMap();
	}

	return 0;
}
unsigned CALLBACK CollisionThread(void* pArguments)
{
	player* p = (player*)pArguments;

	UINT num = 0;

	while (1)
	{
		Sleep(1);

		if (p->getEndThread())
			break;

		continue;


		if (p->getUnits().size() == 0)
			continue;

		if (++num >= p->getUnits().size())
			num = 0;

		Unit* unitMove = p->getUnits()[num];

		if (unitMove->getIsBusy() != 0)
			continue;

		unitMove->addIsBusy(0x02);


		if (unitMove->getUnitnumZerg() == UNITNUM_ZERG_LARVA
			|| unitMove->getUnitnumZerg() == UNITNUM_ZERG_ZERGEGG
			|| unitMove->getBaseStatus().isAir == TRUE)
		{
			unitMove->deleteIsBusy(0x02);
			continue;
		}


		//유닛 끼리 충돌
		for (int i = 0; i < p->getUnits().size(); i++)
		{
			if (unitMove == p->getUnits()[i]) continue;

			Unit* unitHold = p->getUnits()[i];



			if (unitHold) unitHold->addIsBusy(0x02);

			if (unitHold) p->getUnitCollision()->isCollision(unitMove, unitHold);

			if (unitHold) unitHold->deleteIsBusy(0x02);
		}

		//유닛-건물 충돌

		//유닛-중립오브젝트 충돌


		unitMove->deleteIsBusy(0x02);
	}

	return 0;
}



player::player()
	: _zergUpgrade(NULL), _gameMap(NULL), _fog(NULL), _creepManager(NULL), _aStar(NULL), _gameController(NULL)
	, _UnitCollision(NULL)
{
}


player::~player()
{

}

HRESULT player::init(PLAYER playerNum, RACES races)
{
	_myMineral = _showMineral = 50;
	_myGas = _showGas = 0;

	_myControl = _myControlMax = 0;

	_playerNum = playerNum;
	_races = races;

	_isGaming = TRUE;

	_zergUpgrade = new zergUpgrade;

	_fog = new fog;
	_fog->setLinkAdressMyPlayer(this);
	_fog->setLinkAdressGameMap(_gameMap);
	_fog->init();

	_creepManager = new creepManager;
	_creepManager->init(_gameMap);


	_aStar = new aStar;
	_aStar->setLinkAdressGameMap(_gameMap);
	_aStar->init();

	_gameController = new gameController;
	_gameController->init(playerNum, _races);
	_gameController->setLinkAdressMyPlayer(this);
	_gameController->setLinkAdressGameMap(_gameMap);
	_gameController->getMiniMap()->setLinkAdressGameMap(_gameMap);

	_UnitCollision = new UnitCollision;



	//초기 유닛
	initStartUnit();


	unsigned int threadId = 0;
	_hAstarThread		= (HANDLE)_beginthreadex(NULL, 0, &AstarThread, this, 0, &threadId);
	_hCreepThread		= (HANDLE)_beginthreadex(NULL, 0, &CreepThread, this, 0, &threadId);
	_hCollisionThread	= (HANDLE)_beginthreadex(NULL, 0, &CollisionThread, this, 0, &threadId);

	_endThread = FALSE;






	return S_OK;
}

void player::release(void)
{
	_endThread = TRUE;

	WaitForSingleObject(_hAstarThread, INFINITE);
	CloseHandle(_hAstarThread);

	WaitForSingleObject(_hCreepThread, INFINITE);
	CloseHandle(_hCreepThread);

	WaitForSingleObject(_hCollisionThread, INFINITE);
	CloseHandle(_hCollisionThread);

	for (UINT i = 0; i < _vUnits.size(); i++)
	{
		SAFE_RELEASEDELETE(_vUnits[i]);
	}
	_vUnits.clear();

	for (UINT i = 0; i < _vBuildings.size(); i++)
	{
		SAFE_RELEASEDELETE(_vBuildings[i]);
	}
	_vBuildings.clear();



	SAFE_RELEASEDELETE(_fog);
	SAFE_DELETE(_creepManager);

	SAFE_DELETE(_aStar);
	SAFE_RELEASEDELETE(_gameController);


	SAFE_DELETE(_zergUpgrade);
}

void player::update(void) 
{
	//치트키
	


	//죽거나 없어져서 무효화된 유닛, 건물 체크
	checkUnitValid();
	checkBuildingVaild();

	//완료된 업그레이드가 있는지 체크
	updateZergUpgrade();

	//유닛 업데이트
	for (UINT i = 0; i < _vUnits.size(); i++)
	{
		if (_vUnits[i]->getValid() == FALSE) continue;

		_vUnits[i]->update();
	}

	//건물 업데이트
	for (UINT i = 0; i < _vBuildings.size(); i++)
	{
		if (_vBuildings[i]->getValid() == FALSE) continue;

		_vBuildings[i]->update();
	}

	//현재 자원계산
	calcResource();

	//카메라안에 보이는 유닛, 건물만 따로 모으기
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

	_fog->render();
}

void player::initStartUnit(void)
{
	POINT ptLocation = { 0, 0 };
	if (_playerNum == PLAYER1)
	{
		ptLocation = _gameMap->getLocationP1();
	}

	zbHatchery* hatchery = new zbHatchery(_playerNum);
	hatchery->setLinkAdressZergUpgrade(_zergUpgrade);
	hatchery->setLinkAdressAstar(_aStar);
	hatchery->setLinkAdressPlayer(this);
	hatchery->init(ptLocation, 3);
	addBuilding(hatchery);

	POINT hatcherySize = BUILDSIZE_HATCHERY;

	ptLocation.y += hatcherySize.y;

	ptLocation.x *= TILESIZE;
	ptLocation.y *= TILESIZE;

	POINT droneSize = UNITSIZE_ZERG_DRONE;

	ptLocation.x += droneSize.x / 2;
	//ptLocation.y += droneSize.y;

	for (int i = 0; i < 4; i++)
	{
		zuDrone* drone = new zuDrone(_playerNum);
		drone->setLinkAdressZergUpgrade(_zergUpgrade);
		drone->setLinkAdressAstar(_aStar);
		drone->setLinkAdressPlayer(this);
		drone->init({ ptLocation.x + i * droneSize.x, ptLocation.y });
		addUnit(drone);
	}

	zuOverlord* overlord = new zuOverlord(_playerNum);
	overlord->setLinkAdressZergUpgrade(_zergUpgrade);
	overlord->setLinkAdressAstar(_aStar);
	overlord->setLinkAdressPlayer(this);
	overlord->init({ ptLocation.x + 100, ptLocation.y - 50});
	addUnit(overlord);

}



void player::checkInCamera(void)
{
	_vUnitsInCamera.clear();		//카메라에 보여주는 유닛들
	_vBuildingsInCamera.clear();	//카메라에 보여주는 건물들

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

	for (UINT i = 0; i < _vBuildings.size(); i++)
	{
		RECT rcBody = _vBuildings[i]->getBattleStatus().rcBody;
		if (IntersectRect(&temp, &rcCamera, &rcBody))
		{
			_vBuildingsInCamera.push_back(_vBuildings[i]);
		}
	}
}

void player::calcResource(void)
{
	if (_showMineral > _myMineral)
	{
		UINT delta = _showMineral - _myMineral;
		delta = delta * 0.1f + 1;
		_showMineral -= delta;
	}
	else if (_showMineral < _myMineral)
	{
		UINT delta = _myMineral - _showMineral;
		delta = delta * 0.1f + 1;
		_showMineral += delta;
	}

	if (_showGas > _myGas)
	{
		UINT delta = _showGas - _myGas;
		delta = delta * 0.1f + 1;
		_showGas -= delta;
	}
	else if (_showGas < _myGas)
	{
		UINT delta = _myGas - _showGas;
		delta = delta * 0.1f + 1;
		_showGas += delta;
	}
}

void player::updateZergUpgrade(void)
{
	while (_vZergUpgradeComplete.size() > 0)
	{
		_zergUpgrade->upgradeComplete(_vZergUpgradeComplete[0]);

		switch (_vZergUpgradeComplete[0])
		{
			case UPGRADE_ZERG_MELEEATTACKS:		//저그 지상유닛 근접 공격
			case UPGRADE_ZERG_MISSILEATTACKS:	//저그 지상유닛 원거리 공격
			case UPGRADE_ZERG_CARAPACE:			//저그 지상유닛 방어력
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getBaseStatus().isAir == TRUE) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			case UPGRADE_ZERG_FLYERATTACKS:		//저그 공중유닛 공격
			case UPGRADE_ZERG_FLYERCARAPACE:		//저그 공중유닛 방어력
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getBaseStatus().isAir == FALSE) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;
		}

		_vZergUpgradeComplete.erase(_vZergUpgradeComplete.begin());
	}

	while (_vZergEvolutionComplete.size() > 0)
	{
		_zergUpgrade->evolutionComplete(_vZergEvolutionComplete[0]);

		switch (_vZergEvolutionComplete[0])
		{
			//case EVOLUTION_ZERG_BURROW:					//저그 버러우 업글
			case EVOLUTION_ZERG_METABOLICK_BOOST:			//저글링 이속업
			case EVOLUTION_ZERG_ADRENAL_GLANDS:				//저글링 아드레날린
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_ZERGLING) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			//case EVOLUTION_ZERG_VECTRAL_SACS:				//오버로드 수송업
			case EVOLUTION_ZERG_ANTENNAE:					//오버로드 시야업
			case EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:		//오버로드 이속업
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_OVERLORD) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			case EVOLUTION_ZERG_MUSCULAR_AUGMENTS:			//히드라 이속업
			case EVOLUTION_ZERG_GROOVED_SPINES:				//히드라 사정거리업
			//case EVOLUTION_ZERG_LURKER_ASPECT:			//럴커 업글
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_OVERLORD) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;
			
			//case EVOLUTION_ZERG_SPAWN_BROODLING:			//퀸 브루드링 업글
			//case EVOLUTION_ZERG_ENSNARE:					//퀸 인스테어 업글
			case EVOLUTION_ZERG_GAMETE_MEIOSIS:				//퀸 마나업
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_QUEEN) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			case EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:			//울트라 이속업
			case EVOLUTION_ZERG_CHITINOUS_PLATING:			//울트라 방업(+2)
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_ULTRALISK) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			//case EVOLUTION_ZERG_PLAGUE:						//디파일러 플레이그
			//case EVOLUTION_ZERG_CONSUME:					//디파일러 컨슘
			case EVOLUTION_ZERG_METASYNAPTIC_NODE:			//디파일러 마나업
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_DEFILER) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;
		}

		_vZergEvolutionComplete.erase(_vZergEvolutionComplete.begin());
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

bool player::canResource(UINT mineral, UINT gas)
{
	if (_myMineral >= mineral && _myGas >= gas)
	{
		return true;
	}

	if (_myMineral < mineral)
	{
		//미네랄 부족
		if (SOUNDMANAGER->isPlaySound(L"zaderr00") == FALSE)
		{
			SOUNDMANAGER->play(L"zaderr00");
		}
	}
	else if (_myGas < gas)
	{
		if (SOUNDMANAGER->isPlaySound(L"zaderr01") == FALSE)
		{
			//가스 부족
			SOUNDMANAGER->play(L"zaderr01");
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

	if (_myMineral < mineral)
	{
		//미네랄 부족
		if (SOUNDMANAGER->isPlaySound(L"zaderr00") == FALSE)
		{
			SOUNDMANAGER->play(L"zaderr00");
		}
	}
	else if (_myGas < gas)
	{
		if (SOUNDMANAGER->isPlaySound(L"zaderr01") == FALSE)
		{
			//가스 부족
			SOUNDMANAGER->play(L"zaderr01");
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
			if (SOUNDMANAGER->isPlaySound(L"zaderr00") == FALSE)
			{
				SOUNDMANAGER->play(L"zaderr00");
			}
		}
		else if (_myGas < gas)
		{
			//가스 부족
			if (SOUNDMANAGER->isPlaySound(L"zaderr01") == FALSE)
			{
				//가스 부족
				SOUNDMANAGER->play(L"zaderr01");
			}
		}
		else if ((_myControl + control) > _myControlMax)
		{
			//인구수 부족
			if (SOUNDMANAGER->isPlaySound(L"zaderr02") == FALSE)
			{
				SOUNDMANAGER->play(L"zaderr02");
			}
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
			if (_vUnits[i]->getBattleStatus().isDead)
			{
				UNITNUM_ZERG unitNumZ = _vUnits[i]->getUnitnumZerg();

				POINT pt = _vUnits[i]->getBattleStatus().pt.toPoint();

				switch (unitNumZ)
				{
				case UNITNUM_ZERG_LARVA:			EFFECTMANAGER->play(L"ZU-larva-Death",		pt.x, pt.y);	break;
				case UNITNUM_ZERG_ZERGEGG:			EFFECTMANAGER->play(L"ZU-zergegg-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_DRONE:			EFFECTMANAGER->play(L"ZU-drone-Death",		pt.x, pt.y);	break;
				case UNITNUM_ZERG_ZERGLING:			EFFECTMANAGER->play(L"ZU-zergling-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_HYDRALISK:		EFFECTMANAGER->play(L"ZU-hydralisk-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_LURKER:			EFFECTMANAGER->play(L"ZU-lurker-Death",		pt.x, pt.y);	break;
				case UNITNUM_ZERG_LURKEREGG:		EFFECTMANAGER->play(L"ZU-lurkeregg-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_ULTRALISK:		EFFECTMANAGER->play(L"ZU-ultralisk-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_BROODLING:		break;
				case UNITNUM_ZERG_DEFILER:			EFFECTMANAGER->play(L"ZU-defiler-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_INFESTEDTERRAN:	break;
				case UNITNUM_ZERG_OVERLORD:			break; //EFFECTMANAGER->play(L"ZU-overlord-Death"
				case UNITNUM_ZERG_MUTALISK:			EFFECTMANAGER->play(L"ZU-mutalisk-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_SCOURGE:			EFFECTMANAGER->play(L"ZU-scourge-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_QUEEN:			EFFECTMANAGER->play(L"ZU-queen-Death",		pt.x, pt.y);	break;
				case UNITNUM_ZERG_COCOON:			EFFECTMANAGER->play(L"ZU-cocoon-Death",		pt.x, pt.y);	break;
				case UNITNUM_ZERG_GUADIAN:			EFFECTMANAGER->play(L"ZU-guadian-Death",	pt.x, pt.y);	break;
				case UNITNUM_ZERG_DEVOURER:			EFFECTMANAGER->play(L"ZU-devourer-Death",	pt.x, pt.y);	break;
				}
			}

			if (_vUnits[i]->getIsBusy() == 0)
			{
				_myControl		-= _vUnits[i]->getBaseStatus().unitControl;
				_myControlMax	-= _vUnits[i]->getBaseStatus().publicControl;

				_gameController->changeSelectInfoToNextObect(_vUnits[i]);
				SAFE_RELEASEDELETE(_vUnits[i]);
				_vUnits.erase(_vUnits.begin() + i);
			}


		}
		else ++i;
	}
}

void player::checkBuildingVaild(void)
{
	for (int i = 0; i < _vBuildings.size(); )
	{
		if (_vBuildings[i]->getValid() == false && _vBuildings[i]->getIsBusy() == 0)
		{
			//크립 제거 추가
			BUILDINGNUM_ZERG buildingNum = _vBuildings[i]->getBuildingNumZerg();
			
			if (buildingNum == BUILDINGNUM_ZERG_HATCHERY
				|| buildingNum == BUILDINGNUM_ZERG_LAIR
				|| buildingNum == BUILDINGNUM_ZERG_HIVE)
			{
				//다음 오브젝트가 없거나, 있어도 HP가 없어서 죽은경우 제거
				if (_vBuildings[i]->getNextObject() == NULL
					|| (_vBuildings[i]->getNextObject() != NULL && _vBuildings[i]->getBattleStatus().isDead == TRUE))
				{
					_creepManager->deleteCreep(_vBuildings[i]->getBattleStatus().ptTile, BUILDSIZE_HATCHERY);
				}
			}
			else if (buildingNum == BUILDINGNUM_ZERG_CREEPCOLONY
					|| buildingNum == BUILDINGNUM_ZERG_SUNKENCOLONY
					|| buildingNum == BUILDINGNUM_ZERG_SPORECOLONY)
			{
				if (_vBuildings[i]->getNextObject() == NULL
					|| (_vBuildings[i]->getNextObject() != NULL && _vBuildings[i]->getBattleStatus().isDead == TRUE))
				{
					_creepManager->deleteCreep(_vBuildings[i]->getBattleStatus().ptTile, BUILDSIZE_CREEPCOLONY);
				}
			}
			//~크립 제거 추가

			//인구수 업데이트
			_myControlMax -= _vBuildings[i]->getBaseStatus().publicControl;

			//선택된 오브젝트면 다음 오브젝트로 바꾸고
			_gameController->changeSelectInfoToNextObect(_vBuildings[i]);

			//맵에서 제거
			if (_vBuildings[i]->getNextObject() == NULL
				|| (_vBuildings[i]->getNextObject() != NULL && _vBuildings[i]->getBattleStatus().isDead == TRUE))
			{
				POINT ptTile = _vBuildings[i]->getBattleStatus().ptTile;
				RECT rcBody = _vBuildings[i]->getBattleStatus().rcBody;
				int width = (rcBody.right - rcBody.left) / TILESIZE;
				int height = (rcBody.bottom - rcBody.top) / TILESIZE;

				for (int i = 0; i < width; i++)
				{
					for (int j = 0; j < height; j++)
					{
						int idx = ptTile.x + i;
						int idy = ptTile.y + j;

						if (_gameMap->getTiles()[idx][idy].obj == OBJECT_BUILDING_GAS_START_PLAYER1 + _playerNum)
						{
							_gameMap->getTiles()[idx][idy].obj = OBJECT_GAS_START;
						}
						else if (_gameMap->getTiles()[idx][idy].obj == OBJECT_BUILDING_GAS_PLAYER1 + _playerNum)
						{
							_gameMap->getTiles()[idx][idy].obj = OBJECT_GAS_BODY;
						}
						else
						{
							_gameMap->getTiles()[idx][idy].obj = OBJECT_NONE;
						}
					}
				}
			}
			//~맵에서 제거



			//삭제 
			SAFE_RELEASEDELETE(_vBuildings[i]);
			_vBuildings.erase(_vBuildings.begin() + i);
		}
		else ++i;
	}
}

void player::addUnit(Unit* unit)
{
	_myControl += unit->getBaseStatus().unitControl;
	_myControlMax += unit->getBaseStatus().publicControl;

	_vUnits.push_back(unit); 
}

void player::addBuilding(Building* building)
{
	//크립생성
	BUILDINGNUM_ZERG buildingNum = building->getBuildingNumZerg();
	if (buildingNum == BUILDINGNUM_ZERG_HATCHERY
		|| buildingNum == BUILDINGNUM_ZERG_LAIR
		|| buildingNum == BUILDINGNUM_ZERG_HIVE)
	{
		_creepManager->addCreep(building->getBattleStatus().ptTile, BUILDSIZE_HATCHERY);
	}
	else if (buildingNum == BUILDINGNUM_ZERG_CREEPCOLONY
		|| buildingNum == BUILDINGNUM_ZERG_SUNKENCOLONY
		|| buildingNum == BUILDINGNUM_ZERG_SPORECOLONY)
	{
		_creepManager->addCreep(building->getBattleStatus().ptTile, BUILDSIZE_CREEPCOLONY);
	}

	//인구수 계산
	_myControlMax += building->getBaseStatus().publicControl;

	//맵에 등록
	POINT ptTile = building->getBattleStatus().ptTile;
	RECT rcBody = building->getBattleStatus().rcBody;
	int width =  (rcBody.right - rcBody.left) / TILESIZE;
	int height = (rcBody.bottom - rcBody.top) / TILESIZE;
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int idx = ptTile.x + i;
			int idy = ptTile.y + j;

			if (_gameMap->getTiles()[idx][idy].obj == OBJECT_GAS_START)
			{
				_gameMap->getTiles()[idx][idy].obj = OBJECT_BUILDING_GAS_START_PLAYER1 + _playerNum;
			}
			else if(_gameMap->getTiles()[idx][idy].obj == OBJECT_GAS_BODY)
			{
				_gameMap->getTiles()[idx][idy].obj = OBJECT_BUILDING_GAS_PLAYER1 + _playerNum;
			}
			else
			{
				_gameMap->getTiles()[idx][idy].obj = OBJECT_BUILDING_PLAYER1 + _playerNum;
			}
		}
	}

	_vBuildings.push_back(building);
}
