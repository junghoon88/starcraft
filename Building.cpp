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
		//Ŭ�� �� ������Ʈ�� 
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
				case COMMAND_UPGRADE_ZERG_MELEEATTACKS:				_player->addZergUpgradeComplete(UPGRADE_ZERG_MELEEATTACKS	);					break;	//���� �������� ���� ����
				case COMMAND_UPGRADE_ZERG_MISSILEATTACKS:			_player->addZergUpgradeComplete(UPGRADE_ZERG_MISSILEATTACKS	);					break;	//���� �������� ���Ÿ� ����
				case COMMAND_UPGRADE_ZERG_CARAPACE:					_player->addZergUpgradeComplete(UPGRADE_ZERG_CARAPACE		);					break;	//���� �������� ����
				case COMMAND_UPGRADE_ZERG_FLYERATTACKS:				_player->addZergUpgradeComplete(UPGRADE_ZERG_FLYERATTACKS	);					break;	//���� �������� ����
				case COMMAND_UPGRADE_ZERG_FLYERCARAPACE:			_player->addZergUpgradeComplete(UPGRADE_ZERG_FLYERCARAPACE	);					break;	//���� �������� ����

				//EVOLUTION
				case COMMAND_EVOLUTION_ZERG_BURROW:					_player->addZergEvolutionComplete(EVOLUTION_ZERG_BURROW					);		break;	//���� ������ ����
				case COMMAND_EVOLUTION_ZERG_METABOLICK_BOOST:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_METABOLICK_BOOST		);		break;	//���۸� �̼Ӿ�
				case COMMAND_EVOLUTION_ZERG_ADRENAL_GLANDS:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_ADRENAL_GLANDS			);		break;	//���۸� �Ƶ巹����
				case COMMAND_EVOLUTION_ZERG_VECTRAL_SACS:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_VECTRAL_SACS			);		break;	//�����ε� ���۾�
				case COMMAND_EVOLUTION_ZERG_ANTENNAE:				_player->addZergEvolutionComplete(EVOLUTION_ZERG_ANTENNAE				);		break;	//�����ε� �þ߾�
				case COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:	_player->addZergEvolutionComplete(EVOLUTION_ZERG_PNEUMATIZED_CARAPACE	);		break;	//�����ε� �̼Ӿ�
				case COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_MUSCULAR_AUGMENTS		);		break;	//����� �̼Ӿ�
				case COMMAND_EVOLUTION_ZERG_GROOVED_SPINES:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_GROOVED_SPINES			);		break;	//����� �����Ÿ���
				case COMMAND_EVOLUTION_ZERG_LURKER_ASPECT:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_LURKER_ASPECT			);		break;	//��Ŀ ����
				case COMMAND_EVOLUTION_ZERG_SPAWN_BROODLING:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_SPAWN_BROODLING		);		break;	//�� ���帵 ����
				case COMMAND_EVOLUTION_ZERG_ENSNARE:				_player->addZergEvolutionComplete(EVOLUTION_ZERG_ENSNARE				);		break;	//�� �ν��׾� ����
				case COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS:			_player->addZergEvolutionComplete(EVOLUTION_ZERG_GAMETE_MEIOSIS			);		break;	//�� ������
				case COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_ANABOLIC_SYNTHESIS		);		break;	//��Ʈ�� �̼Ӿ�
				case COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_CHITINOUS_PLATING		);		break;	//��Ʈ�� ���(+2)
				case COMMAND_EVOLUTION_ZERG_PLAGUE:					_player->addZergEvolutionComplete(EVOLUTION_ZERG_PLAGUE					);		break;	//�����Ϸ� �÷��̱�
				case COMMAND_EVOLUTION_ZERG_CONSUME:				_player->addZergEvolutionComplete(EVOLUTION_ZERG_CONSUME				);		break;	//�����Ϸ� ����
				case COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE:		_player->addZergEvolutionComplete(EVOLUTION_ZERG_METASYNAPTIC_NODE		);		break;	//�����Ϸ� ������
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
