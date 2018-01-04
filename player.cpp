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

		if (p->getUnitBusy())
			continue;

		if (units.size() == 0)
			continue;

		if (++num >= units.size()) 
			num = 0;



		tagBattleStatus battleStatus = units[num]->getBattleStatus();

		//AStar �� ������� ������ ����
		if (battleStatus.useAstar == FALSE)
			continue;

		//AStar �� ����ϴµ� ����� �������� ����
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
	}

	return 0;
}
unsigned CALLBACK CollisionThread(void* pArguments)
{
	player* p = (player*)pArguments;

	while (1)
	{
		Sleep(10);

		if (p->getEndThread())
		{
			break;
		}
	}

	return 0;
}



player::player()
	: _zergUpgrade(NULL), _gameMap(NULL), _fog(NULL), _creepManager(NULL), _aStar(NULL), _gameController(NULL)
{
}


player::~player()
{

}

HRESULT player::init(PLAYER playerNum, RACES races)
{
	_myMineral = _showMineral = 10000;
	_myGas = _showGas = 10000;

	_myControl = _myControlMax = 0;

	_unitBusy = false;
	_buildingBusy = false;


	_playerNum = playerNum;
	_races = races;

	_isGaming = TRUE;

	_zergUpgrade = new zergUpgrade;

	_fog = new fog;
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


	//debug
	for (int i = 0; i < 13; i++)
	{
		zuDrone* drone = new zuDrone(_playerNum);
		drone->setLinkAdressZergUpgrade(_zergUpgrade);
		drone->setLinkAdressAstar(_aStar);
		drone->setLinkAdressPlayer(this);
		drone->init({ 200, 200 });

		addUnit(drone);
	}


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
		while (_vUnits[i]->getIsBusy() == true)
		{
			Sleep(1);
		}
		SAFE_RELEASEDELETE(_vUnits[i]);
	}
	_vUnits.clear();


	SAFE_RELEASEDELETE(_fog);
	SAFE_DELETE(_creepManager);

	SAFE_RELEASEDELETE(_aStar);
	SAFE_RELEASEDELETE(_gameController);


	SAFE_DELETE(_zergUpgrade);
}

void player::update(void) 
{
	checkUnitValid();
	checkBuildingVaild();

	updateZergUpgrade();

	for (UINT i = 0; i < _vUnits.size(); i++)
	{
		_vUnits[i]->update();
	}

	for (UINT i = 0; i < _vBuildings.size(); i++)
	{
		_vBuildings[i]->update();
	}

	calcResource();

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
	_vUnitsInCamera.clear();		//ī�޶� �����ִ� ���ֵ�
	_vBuildingsInCamera.clear();	//ī�޶� �����ִ� �ǹ���

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
	for (int i = 0; i < _vZergUpgradeComplete.size(); i++)
	{
		_zergUpgrade->upgradeComplete(_vZergUpgradeComplete[i]);

		switch (_vZergUpgradeComplete[i])
		{
			case UPGRADE_ZERG_MELEEATTACKS:		//���� �������� ���� ����
			case UPGRADE_ZERG_MISSILEATTACKS:	//���� �������� ���Ÿ� ����
			case UPGRADE_ZERG_CARAPACE:			//���� �������� ����
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getBaseStatus().isAir == TRUE) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			case UPGRADE_ZERG_FLYERATTACKS:		//���� �������� ����
			case UPGRADE_ZERG_FLYERCARAPACE:		//���� �������� ����
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getBaseStatus().isAir == FALSE) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;
		}

		_vZergUpgradeComplete.erase(_vZergUpgradeComplete.begin() + i);
	}

	for (int i = 0; i < _vZergEvolutionComplete.size(); i++)
	{
		_zergUpgrade->evolutionComplete(_vZergEvolutionComplete[i]);

		switch (_vZergEvolutionComplete[i])
		{
			//case EVOLUTION_ZERG_BURROW:					//���� ������ ����
			case EVOLUTION_ZERG_METABOLICK_BOOST:			//���۸� �̼Ӿ�
			case EVOLUTION_ZERG_ADRENAL_GLANDS:				//���۸� �Ƶ巹����
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_ZERGLING) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			//case EVOLUTION_ZERG_VECTRAL_SACS:				//�����ε� ���۾�
			case EVOLUTION_ZERG_ANTENNAE:					//�����ε� �þ߾�
			case EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:		//�����ε� �̼Ӿ�
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_OVERLORD) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			case EVOLUTION_ZERG_MUSCULAR_AUGMENTS:			//����� �̼Ӿ�
			case EVOLUTION_ZERG_GROOVED_SPINES:				//����� �����Ÿ���
			//case EVOLUTION_ZERG_LURKER_ASPECT:			//��Ŀ ����
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_OVERLORD) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;
			
			//case EVOLUTION_ZERG_SPAWN_BROODLING:			//�� ���帵 ����
			//case EVOLUTION_ZERG_ENSNARE:					//�� �ν��׾� ����
			case EVOLUTION_ZERG_GAMETE_MEIOSIS:				//�� ������
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_QUEEN) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			case EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:			//��Ʈ�� �̼Ӿ�
			case EVOLUTION_ZERG_CHITINOUS_PLATING:			//��Ʈ�� ���(+2)
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_ULTRALISK) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;

			//case EVOLUTION_ZERG_PLAGUE:						//�����Ϸ� �÷��̱�
			//case EVOLUTION_ZERG_CONSUME:					//�����Ϸ� ����
			case EVOLUTION_ZERG_METASYNAPTIC_NODE:			//�����Ϸ� ������
				for (int j = 0; j < _vUnits.size(); j++)
				{
					if (_vUnits[j]->getUnitnumZerg() != UNITNUM_ZERG_DEFILER) continue;

					_vUnits[j]->updateBattleStatus();
				}
			break;
		}

		_vZergEvolutionComplete.erase(_vZergEvolutionComplete.begin() + i);
	}
}



bool player::isHaveBuilding(BUILDINGNUM_ZERG num)
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
			//�̳׶� ����
		}
		else if (_myGas < gas)
		{
			//���� ����
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
			//�̳׶� ����
		}
		else if (_myGas < gas)
		{
			//���� ����
		}
		else if ((_myControl + control) > _myControlMax)
		{
			//�α��� ����
		}
	}


	return false;
}



void player::checkUnitValid(void)
{
	_unitBusy = true;
	for (int i = 0; i < _vUnits.size(); )
	{
		if (_vUnits[i]->getValid() == false)
		{

			if (_vUnits[i]->getIsBusy() == false)
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
	_unitBusy = false;
}

void player::checkBuildingVaild(void)
{
	for (int i = 0; i < _vBuildings.size(); )
	{
		if (_vBuildings[i]->getValid() == false)
		{
			//ũ�� ���� �߰�
			BUILDINGNUM_ZERG buildingNum = _vBuildings[i]->getBuildingNumZerg();
			
			if (buildingNum == BUILDINGNUM_ZERG_HATCHERY
				|| buildingNum == BUILDINGNUM_ZERG_LAIR
				|| buildingNum == BUILDINGNUM_ZERG_HIVE)
			{
				if (_vBuildings[i]->getNextObject() == NULL)
				{
					_creepManager->deleteCreep(_vBuildings[i]->getBattleStatus().ptTile, BUILDSIZE_HATCHERY);
				}
				else
				{
					if (_vBuildings[i]->getBattleStatus().curHP < 1.0f)
					{
						_creepManager->deleteCreep(_vBuildings[i]->getBattleStatus().ptTile, BUILDSIZE_HATCHERY);
					}
				}
			}
			else if (buildingNum == BUILDINGNUM_ZERG_CREEPCOLONY
					|| buildingNum == BUILDINGNUM_ZERG_SUNKENCOLONY
					|| buildingNum == BUILDINGNUM_ZERG_SPORECOLONY)
			{
				if (_vBuildings[i]->getNextObject() == NULL)
				{
					_creepManager->deleteCreep(_vBuildings[i]->getBattleStatus().ptTile, BUILDSIZE_CREEPCOLONY);
				}
				else
				{
					if (_vBuildings[i]->getBattleStatus().curHP < 1.0f)
					{
						_creepManager->deleteCreep(_vBuildings[i]->getBattleStatus().ptTile, BUILDSIZE_CREEPCOLONY);
					}
				}
			}
			//~ũ�� ���� �߰�

			//�α��� ������Ʈ
			_myControlMax -= _vBuildings[i]->getBaseStatus().publicControl;

			//���õ� ������Ʈ�� ���� ������Ʈ�� �ٲٰ�
			_gameController->changeSelectInfoToNextObect(_vBuildings[i]);

			//���� 
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

	_myControlMax += building->getBaseStatus().publicControl;


	_vBuildings.push_back(building);
}
