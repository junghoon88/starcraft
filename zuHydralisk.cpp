#include "stdafx.h"
#include "zuHydralisk.h"
#include "zergDefine.h"
#include "player.h"


zuHydralisk::zuHydralisk(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_HYDRALISK;

}


zuHydralisk::~zuHydralisk()
{
}

HRESULT zuHydralisk::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}

void zuHydralisk::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Hydralisk");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-hydralisk-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-hydralisk-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-hydralisk-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-hydralisk-Stat2");

	_baseStatus.unitControl = 1.0f;

	_baseStatus.maxHP = 80.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 6.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;
	_baseStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METASYNAPTIC_NODE].complete == false) ? 3.71f : 5.57f;

	_baseStatus.unitSize = UNITSIZE_MEDIUM;
	_baseStatus.transportslots = 2;
	_baseStatus.armor = 0;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = TRUE;

	_baseStatus.GWable = TRUE;
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_MISSILE;
	_stprintf(_baseStatus.GWname, L"Needle Spines");
	_baseStatus.GWdamage = 10;
	_baseStatus.GWdamagePlus = 1;
	_baseStatus.GWmaxHit = 1;
	_baseStatus.GWdamageType = DAMAGETYPE_EXPLOSIVE;
	_baseStatus.GWcooldown = 15.0;
	_baseStatus.GWattackRange = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_GROOVED_SPINES].complete == false) ? 4.0f : 5.0f; //업글시 5

	_baseStatus.AWable = TRUE;
	_baseStatus.AWAttackType = ATTACKTYPE_ZERG_MISSILE;
	_stprintf(_baseStatus.AWname, L"Needle Spines");
	_baseStatus.AWdamage = 10;
	_baseStatus.AWdamagePlus = 1;
	_baseStatus.AWmaxHit = 1;
	_baseStatus.AWdamageType = DAMAGETYPE_EXPLOSIVE;
	_baseStatus.AWcooldown = 15.0;
	_baseStatus.AWattackRange = 4.0f; //업글시 5

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_ATTACK;
	_baseStatus.commands[3] = COMMAND_PATROL;
	_baseStatus.commands[4] = COMMAND_HOLD;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_UNIT_LURKER;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_BURROW;
}
void zuHydralisk::initBattleStatus(POINT pt)
{
	//BattleStatus
	_battleStatus.unitState = UNITSTATE_STOP;
	_battleStatus.curCommand = COMMAND_STOP;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;
	_battleStatus.maxHP = _baseStatus.maxHP;

	_battleStatus.pt.set((float)pt.x, (float)pt.y);
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
	_battleStatus.angleDeg = 315.0f;
	_battleStatus.direction;
}


void zuHydralisk::release(void)
{

}

void zuHydralisk::update(void)
{
	Unit::update();
}

void zuHydralisk::render(void)
{
	Unit::render();
}

void zuHydralisk::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_HYDRALISK;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuHydralisk::updateBattleStatus(void)
{
	Unit::updateBattleStatus();

	_baseStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METASYNAPTIC_NODE].complete == false) ? 3.71f : 5.57f;
	_battleStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METASYNAPTIC_NODE].complete == false) ? 3.71f : 5.57f;
	_baseStatus.GWattackRange = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_GROOVED_SPINES].complete == false) ? 4.0f : 5.0f; //업글시 5

}

void zuHydralisk::updateImageFrame(void)
{
	float tick = TIMEMANAGER->getElapsedTime();

	if (_isBurrowing)
	{
		_battleStatus.unitState = UNITSTATE_STOP;

		if (_battleStatus.bodyFrame.y != 12)
		{
			_battleStatus.bodyFrame.x = 0;
			_battleStatus.bodyFrame.y = 12;
			_battleStatus.bodyFrameTime = 0.0f;
		}

		_battleStatus.bodyFrameTime += tick;
		if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
		{
			_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;
			_battleStatus.bodyFrame.x++;
			if (_battleStatus.bodyFrame.x > 7)
			{
				_battleStatus.bodyFrame.x = 7;
				_isBurrowing = false;
				_battleStatus.isBurrow = true;
				_battleStatus.angleDeg = 315.0f;
			}
		}
	}
	else if (_isUnburrowing)
	{
		_battleStatus.bodyFrameTime += tick;
		if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME / 4)
		{
			_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME / 4;
			_battleStatus.bodyFrame.x--;
			if (_battleStatus.bodyFrame.x < 0)
			{
				_battleStatus.bodyFrame.x = 3;
				_isUnburrowing = false;
				_battleStatus.isBurrow = false;
				_battleStatus.curCommand = COMMAND_STOP;
				_battleStatus.oldCommand = COMMAND_STOP;

				_battleStatus.bodyFrame.y = 0;
			}
		}
	}
	else
	{
		if (_battleStatus.isBurrow)
			return;

		Unit::setImageFrameForAngle();

		if (_battleStatus.unitState == UNITSTATE_STOP)
		{
			//0
			_battleStatus.bodyFrame.y = 0;
			_battleStatus.bodyFrameTime = 0.0f;
		}
		else if (_battleStatus.unitState == UNITSTATE_MOVE)
		{
			//5, 6, 7, 8, 9, 10, 11
			if (_battleStatus.bodyFrame.y >= 5 && _battleStatus.bodyFrame.y <= 11)
			{
				_battleStatus.bodyFrameTime += tick;
				if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
				{
					_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

					_battleStatus.bodyFrame.y++;
					if (_battleStatus.bodyFrame.y > 11)
					{
						_battleStatus.bodyFrame.y = 5;
					}
				}
			}
			else
			{
				_battleStatus.bodyFrame.y = 5;
				_battleStatus.bodyFrameTime = 0.0f;
			}
		}
		else if (_battleStatus.unitState == UNITSTATE_ATTACK)
		{
			if (_battleStatus.targetObject == NULL)
			{
				_battleStatus.bodyFrame.y = 0;
				_battleStatus.bodyFrameTime = 0.0f;
				return;
			}

			float attackTime = (_battleStatus.targetObject->getBaseStatus().isAir) ? _baseStatus.AWcooldown : _baseStatus.GWcooldown;
			attackTime = attackTime * UNIT_ATTACK_FPS_TIME / 4; //공격이 4프레임이니까 공격시간을 4로 나눠서 적용한다.

			//1, 2, 3, 4
			if (_battleStatus.bodyFrame.y >= 1 && _battleStatus.bodyFrame.y <= 4)
			{
				_battleStatus.bodyFrameTime += tick;
				if (_battleStatus.bodyFrameTime >= attackTime)
				{
					_battleStatus.bodyFrameTime -= attackTime;

					_battleStatus.bodyFrame.y++;
					if (_battleStatus.bodyFrame.y > 4)
					{
						_battleStatus.bodyFrame.y = 1;
						_battleStatus.targetObject->hitDamage(this);

						switch (_battleStatus.bodyFrame.x)
						{
						case 0:	EFFECTMANAGER->play(L"ZU-hydralisk-Bullet000", _battleStatus.pt.x - 24 + 86/2 /*- MAINCAMERA->getCameraX()*/, _battleStatus.pt.y - 80 + 122/2 /*- MAINCAMERA->getCameraY()*/);	break;
						case 1:	EFFECTMANAGER->play(L"ZU-hydralisk-Bullet045", _battleStatus.pt.x - 19 + 86/2 /*- MAINCAMERA->getCameraX()*/, _battleStatus.pt.y - 68 + 122/2 /*- MAINCAMERA->getCameraY()*/);	break;
						case 2:	EFFECTMANAGER->play(L"ZU-hydralisk-Bullet090", _battleStatus.pt.x -  6 + 86/2 /*- MAINCAMERA->getCameraX()*/, _battleStatus.pt.y - 61 + 122/2 /*- MAINCAMERA->getCameraY()*/);	break;
						case 3:	EFFECTMANAGER->play(L"ZU-hydralisk-Bullet135", _battleStatus.pt.x - 15 + 86/2 /*- MAINCAMERA->getCameraX()*/, _battleStatus.pt.y - 54 + 122/2 /*- MAINCAMERA->getCameraY()*/);	break;
						case 4:	EFFECTMANAGER->play(L"ZU-hydralisk-Bullet180", _battleStatus.pt.x - 23 + 86/2 /*- MAINCAMERA->getCameraX()*/, _battleStatus.pt.y - 46 + 122/2 /*- MAINCAMERA->getCameraY()*/);	break;
						case 5:	EFFECTMANAGER->play(L"ZU-hydralisk-Bullet225", _battleStatus.pt.x - 65 + 86/2 /*- MAINCAMERA->getCameraX()*/, _battleStatus.pt.y - 50 + 122/2 /*- MAINCAMERA->getCameraY()*/);	break;
						case 6:	EFFECTMANAGER->play(L"ZU-hydralisk-Bullet270", _battleStatus.pt.x - 76 + 86/2 /*- MAINCAMERA->getCameraX()*/, _battleStatus.pt.y - 59 + 122/2 /*- MAINCAMERA->getCameraY()*/);	break;
						case 7:	EFFECTMANAGER->play(L"ZU-hydralisk-Bullet315", _battleStatus.pt.x - 64 + 86/2 /*- MAINCAMERA->getCameraX()*/, _battleStatus.pt.y - 68 + 122/2 /*- MAINCAMERA->getCameraY()*/);	break;
						}

						if (_battleStatus.targetObject->getBattleStatus().isDead)
						{
							_battleStatus.targetObject = NULL;
							_battleStatus.unitState == UNITSTATE_STOP;
						}
					}
				}
			}
			else
			{
				_battleStatus.bodyFrame.y = 1;
				_battleStatus.bodyFrameTime = 0.0f;
			}
		}
	}
}


void zuHydralisk::updateCommandSet(void)
{
	if (_battleStatus.isBurrow)
	{
		_baseStatus.commands[0] = COMMAND_NONE;
		_baseStatus.commands[1] = COMMAND_NONE;
		_baseStatus.commands[2] = COMMAND_NONE;
		_baseStatus.commands[3] = COMMAND_NONE;
		_baseStatus.commands[4] = COMMAND_NONE;
		_baseStatus.commands[5] = COMMAND_NONE;
		_baseStatus.commands[6] = COMMAND_NONE;
		_baseStatus.commands[7] = COMMAND_NONE;
		_baseStatus.commands[8] = COMMAND_UNBURROW;
	}
	else
	{
		_baseStatus.commands[0] = COMMAND_MOVE;
		_baseStatus.commands[1] = COMMAND_STOP;
		_baseStatus.commands[2] = COMMAND_ATTACK;
		_baseStatus.commands[3] = COMMAND_PATROL;
		_baseStatus.commands[4] = COMMAND_HOLD;
		_baseStatus.commands[5] = COMMAND_NONE;
		_baseStatus.commands[6] = COMMAND_UNIT_LURKER;
		_baseStatus.commands[7] = COMMAND_NONE;
		_baseStatus.commands[8] = COMMAND_BURROW;
	}
}


void zuHydralisk::procCommands(void)
{
	Unit::procCommands();

	if (_battleStatus.curCommand == COMMAND_UNIT_LURKER)
	{
		tagProduction buildCost = _player->getZergProductionInfo()->getZUProductionInfo(UNITNUM_ZERG_LURKER);

		//내가 차지하고 있는 인구수를 빼준다.
		buildCost.control = buildCost.control - _baseStatus.unitControl;

		if (_player->useResource(buildCost.costMinerals, buildCost.costGas, buildCost.control))
		{
			//성공
			zuLurkerEgg* egg = new zuLurkerEgg(_playerNum);
			egg->setLinkAdressZergUpgrade(_zergUpgrade);
			egg->setLinkAdressAstar(_aStar);
			egg->setLinkAdressPlayer(_player);
			egg->init(_battleStatus.pt.toPoint());

			_nextObject = egg;
			_valid = false;

			_player->addUnit(egg);
		}

		_battleStatus.curCommand = COMMAND_NONE;
	}

}
