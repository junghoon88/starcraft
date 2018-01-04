#include "stdafx.h"
#include "Building.h"
#include "Unit.h"

#include "player.h"

#include "zergDefine.h"


Building::Building()
{
}


Building::~Building()
{
}

HRESULT Building::init(POINT ptTile)
{
	return S_OK;
}

HRESULT Building::init(POINT ptTile, UINT larvaNum)
{
	return S_OK;
}

void Building::release(void)
{
}

void Building::update(void)
{
	procCommands();
	
	updatePosition();
	updateImageFrame();
	updateProcessing();

	if (_battleStatus.clicked)
	{
		//클릭 된 오브젝트만 
		updateCommandSet();
	}
}

void Building::render(int imgOffsetX, int imgOffsetY)
{
	if (_battleStatus.clicked)
	{
		RECT temp = _battleStatus.rcEllipse;
		temp.left -= MAINCAMERA->getCameraX();
		temp.right -= MAINCAMERA->getCameraX();
		temp.top -= MAINCAMERA->getCameraY();
		temp.bottom -= MAINCAMERA->getCameraY();

		RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, temp, PENVERSION_UNITCLICK);
	}


	POINT buildSize = { 0 ,0 };
	POINT buildOffset = { 0, 0 };

	switch (_buildingNumZ)
	{
	case BUILDINGNUM_ZERG_HATCHERY:					  buildSize = BUILDIMAGEOFFSET_HATCHERY			;	break;
	case BUILDINGNUM_ZERG_LAIR:						  buildSize = BUILDIMAGEOFFSET_LAIR				;	break;
	case BUILDINGNUM_ZERG_HIVE:						  buildSize = BUILDIMAGEOFFSET_HIVE				;	break;
	case BUILDINGNUM_ZERG_CREEPCOLONY:				  buildSize = BUILDIMAGEOFFSET_CREEPCOLONY		;	break;
	case BUILDINGNUM_ZERG_SUNKENCOLONY:				  buildSize = BUILDIMAGEOFFSET_SUNKENCOLONY		;	break;
	case BUILDINGNUM_ZERG_SPORECOLONY:				  buildSize = BUILDIMAGEOFFSET_SPORECOLONY		;	break;
	case BUILDINGNUM_ZERG_EXTRACTOR:				  buildSize = BUILDIMAGEOFFSET_EXTRACTOR		;	break;	
	case BUILDINGNUM_ZERG_SPAWNINGPOOL:				  buildSize = BUILDIMAGEOFFSET_SPAWNINGPOOL		;	break;
	case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:			  buildSize = BUILDIMAGEOFFSET_EVOLUTIONCHAMBER	;	break;
	case BUILDINGNUM_ZERG_HYDRALISKDEN:				  buildSize = BUILDIMAGEOFFSET_HYDRALISKDEN		;	break;
	case BUILDINGNUM_ZERG_SPIRE:					  buildSize = BUILDIMAGEOFFSET_SPIRE			;	break;	
	case BUILDINGNUM_ZERG_GREATERSPIRE:				  buildSize = BUILDIMAGEOFFSET_GREATERSPIRE		;	break;
	case BUILDINGNUM_ZERG_QUEENSNEST:				  buildSize = BUILDIMAGEOFFSET_QUEENSNEST		;	break;	
	case BUILDINGNUM_ZERG_NYDUSCANAL:				  buildSize = BUILDIMAGEOFFSET_NYDUSCANAL		;	break;	
	case BUILDINGNUM_ZERG_ULTRALISKCAVERN:			  buildSize = BUILDIMAGEOFFSET_ULTRALISKCAVERN	;	break;
	case BUILDINGNUM_ZERG_DEFILERMOUND:				  buildSize = BUILDIMAGEOFFSET_DEFILERMOUND		;	break;
	//case BUILDINGNUM_ZERG_INFESTEDCOMMANDCENTER:	  buildSize = 
	}

	RECT rcBody = RectMake(
		_battleStatus.ptTile.x * TILESIZE - MAINCAMERA->getCameraX(),
		_battleStatus.ptTile.y * TILESIZE - MAINCAMERA->getCameraY(),
		buildSize.x * TILESIZE,
		buildSize.y * TILESIZE);

	RENDERMANAGER->insertImgFrame(ZORDER_GAMEOBJECT, _baseStatus.imgBody,
		_battleStatus.ptTile.x * TILESIZE - MAINCAMERA->getCameraX() - imgOffsetX,
		_battleStatus.ptTile.y * TILESIZE - MAINCAMERA->getCameraY() - imgOffsetY,
		_battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y, rcBody);

	//debug
	{
		RECT temp = _battleStatus.rcBody;
		temp.left -= MAINCAMERA->getCameraX();
		temp.right -= MAINCAMERA->getCameraX();
		temp.top -= MAINCAMERA->getCameraY();
		temp.bottom -= MAINCAMERA->getCameraY();
		RENDERMANAGER->insertLineRectangle(ZORDER_GAMEDEBUG1, temp, PENVERSION_BLUE1);
	}
}

void Building::updateBattleStatus(void)
{

}
void Building::updatePosition(void)
{

}
void Building::updateImageFrame(void)
{

}

void Building::updateProcessing(void)
{
	if (_processing.type == PROCESSING_NONE)
		return;

	float tick = TIMEMANAGER->getElapsedTime() * BUILDSPEEDMULTIPLY;


	if (_processing.type == PROCESSING_MORPHING)
	{

	}
	else if (_processing.type == PROCESSING_EVOLVING)
	{
		if (_processing.complete == false)
		{
			if (_processing.curTime + tick >= _processing.maxTime)
			{
				_processing.curTime = _processing.maxTime;


				switch (_processing.command)
				{
				//UPGRADE
				case COMMAND_UPGRADE_ZERG_MELEEATTACKS:				_player->addZergUpgradeComplete(UPGRADE_ZERG_MELEEATTACKS	);					break;	//저그 지상유닛 근접 공격
				case COMMAND_UPGRADE_ZERG_MISSILEATTACKS:			_player->addZergUpgradeComplete(UPGRADE_ZERG_MISSILEATTACKS	);					break;	//저그 지상유닛 원거리 공격
				case COMMAND_UPGRADE_ZERG_CARAPACE:					_player->addZergUpgradeComplete(UPGRADE_ZERG_CARAPACE		);					break;	//저그 지상유닛 방어력
				case COMMAND_UPGRADE_ZERG_FLYERATTACKS:				_player->addZergUpgradeComplete(UPGRADE_ZERG_FLYERATTACKS	);					break;	//저그 공중유닛 공격
				case COMMAND_UPGRADE_ZERG_FLYERCARAPACE:			_player->addZergUpgradeComplete(UPGRADE_ZERG_FLYERCARAPACE	);					break;	//저그 공중유닛 방어력

				//EVOLUTION
				case COMMAND_EVOLUTION_ZERG_BURROW:					_player->addZergEvolutionComplete(EVOLUTION_ZERG_BURROW					);		break;	//저그 버러우 업글
				case COMMAND_EVOLUTION_ZERG_METABOLICK_BOOST:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_METABOLICK_BOOST		);		break;	//저글링 이속업
				case COMMAND_EVOLUTION_ZERG_ADRENAL_GLANDS:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_ADRENAL_GLANDS			);		break;	//저글링 아드레날린
				case COMMAND_EVOLUTION_ZERG_VECTRAL_SACS:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_VECTRAL_SACS			);		break;	//오버로드 수송업
				case COMMAND_EVOLUTION_ZERG_ANTENNAE:				_player->addZergEvolutionComplete(EVOLUTION_ZERG_ANTENNAE				);		break;	//오버로드 시야업
				case COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:	_player->addZergEvolutionComplete(EVOLUTION_ZERG_PNEUMATIZED_CARAPACE	);		break;	//오버로드 이속업
				case COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_MUSCULAR_AUGMENTS		);		break;	//히드라 이속업
				case COMMAND_EVOLUTION_ZERG_GROOVED_SPINES:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_GROOVED_SPINES			);		break;	//히드라 사정거리업
				case COMMAND_EVOLUTION_ZERG_LURKER_ASPECT:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_LURKER_ASPECT			);		break;	//럴커 업글
				case COMMAND_EVOLUTION_ZERG_SPAWN_BROODLING:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_SPAWN_BROODLING		);		break;	//퀸 브루드링 업글
				case COMMAND_EVOLUTION_ZERG_ENSNARE:				_player->addZergEvolutionComplete(EVOLUTION_ZERG_ENSNARE				);		break;	//퀸 인스테어 업글
				case COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_GAMETE_MEIOSIS			);		break;	//퀸 마나업
				case COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_ANABOLIC_SYNTHESIS		);		break;	//울트라 이속업
				case COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_CHITINOUS_PLATING		);		break;	//울트라 방업(+2)
				case COMMAND_EVOLUTION_ZERG_PLAGUE:					_player->addZergEvolutionComplete(EVOLUTION_ZERG_PLAGUE					);		break;	//디파일러 플레이그
				case COMMAND_EVOLUTION_ZERG_CONSUME:				_player->addZergEvolutionComplete(EVOLUTION_ZERG_CONSUME				);		break;	//디파일러 컨슘
				case COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_METASYNAPTIC_NODE		);		break;	//디파일러 마나업
				}

				_processing.type = PROCESSING_NONE;
				_processing.complete = true;
			}
			else
			{
				_processing.curTime += tick;
			}
		}
	}
}

void Building::updateCommandSet(void)
{
}

void Building::procCommands(void)
{

}
