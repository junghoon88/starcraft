#include "stdafx.h"
#include "hotkeys.h"


hotkeys::hotkeys()
{
	ZeroMemory(&_hotkey, sizeof(TCHAR)*COMMAND_NUM);

}


hotkeys::~hotkeys()
{
}

HRESULT hotkeys::init(void)
{
	for (int i = 0; i < COMMAND_NUM; i++)
	{
		switch (i)
		{
		case COMMAND_NONE:						_hotkey[i] = 0;			break;
			//COMMON
		case COMMAND_MOVE:						_hotkey[i] = 'M';			break;
		case COMMAND_ESC:						_hotkey[i] = VK_ESCAPE;		break;
		case COMMAND_STOP:						_hotkey[i] = 'S';			break;
		case COMMAND_ATTACK:					_hotkey[i] = 'A';			break;
		case COMMAND_PATROL:					_hotkey[i] = 'P';			break;
		case COMMAND_HOLD:						_hotkey[i] = 'H';			break;
		case COMMAND_GATHER:					_hotkey[i] = 'G';			break;
		case COMMAND_RETURNCARGO:				_hotkey[i] = 'C';			break;
		case COMMAND_BUILD1:					_hotkey[i] = 'B';			break;
		case COMMAND_BUILD2:					_hotkey[i] = 'V';			break;
		case COMMAND_SELECT_LARVA:				_hotkey[i] = 'S';			break;
		case COMMAND_SETRALLYPOINT:				_hotkey[i] = 'R';			break;


		//ZERG
		case COMMAND_BURROW:					_hotkey[i] = 'U';			break;
		case COMMAND_UNBURROW:					_hotkey[i] = 'U';			break;
		case COMMAND_INFEST:					_hotkey[i] = 'I';			break;
		case COMMAND_PARASITE:					_hotkey[i] = 'R';			break;
		case COMMAND_BROODRING:					_hotkey[i] = 'B';			break;
		case COMMAND_ENSNARE:					_hotkey[i] = 'E';			break;
		case COMMAND_CONSUME:					_hotkey[i] = 'C';			break;
		case COMMAND_DARKSWARM:					_hotkey[i] = 'W';			break;
		case COMMAND_PLAGUE:					_hotkey[i] = 'G';			break;
			
		//BUILD
		case COMMAND_BUILD_HATCHERY:			_hotkey[i] = 'H';			break;
		case COMMAND_BUILD_LAIR:				_hotkey[i] = 'L';			break;
		case COMMAND_BUILD_HIVE:				_hotkey[i] = 'H';			break;
		case COMMAND_BUILD_CREEPCOLONY:			_hotkey[i] = 'C';			break;
		case COMMAND_BUILD_SUNKENCOLONY:		_hotkey[i] = 'U';			break;
		case COMMAND_BUILD_SPORECOLONY:			_hotkey[i] = 'S';			break;
		case COMMAND_BUILD_EXTRACTOR:			_hotkey[i] = 'E';			break;
		case COMMAND_BUILD_SPAWNINGPOOL:		_hotkey[i] = 'S';			break;
		case COMMAND_BUILD_EVOLUTIONCHAMBER:	_hotkey[i] = 'V';			break;
		case COMMAND_BUILD_HYDRALISKDEN:		_hotkey[i] = 'D';			break;
		case COMMAND_BUILD_SPIRE:				_hotkey[i] = 'S';			break;
		case COMMAND_BUILD_GREATERSPIRE:		_hotkey[i] = 'G';			break;
		case COMMAND_BUILD_QUEENSNEST:			_hotkey[i] = 'Q';			break;
		case COMMAND_BUILD_NYDUSCANAL:			_hotkey[i] = 'N';			break;
		case COMMAND_BUILD_ULTRALISKCAVERN:		_hotkey[i] = 'U';			break;
		case COMMAND_BUILD_DEFILERMOUND:		_hotkey[i] = 'D';			break;
	
		//UNIT
		case COMMAND_UNIT_DRONE:				_hotkey[i] = 'D';			break;
		case COMMAND_UNIT_ZERGLING:				_hotkey[i] = 'Z';			break;
		case COMMAND_UNIT_OVERLORD:				_hotkey[i] = 'O';			break;
		case COMMAND_UNIT_HYDRALISK:			_hotkey[i] = 'H';			break;
		case COMMAND_UNIT_MUTALISK:				_hotkey[i] = 'M';			break;
		case COMMAND_UNIT_SCOURGE:				_hotkey[i] = 'S';			break;
		case COMMAND_UNIT_QUEEN:				_hotkey[i] = 'Q';			break;
		case COMMAND_UNIT_ULTRALISK:			_hotkey[i] = 'U';			break;
		case COMMAND_UNIT_DEFILER:				_hotkey[i] = 'F';			break;
		case COMMAND_UNIT_LURKER:				_hotkey[i] = 'L';			break;
		case COMMAND_UNIT_GUADIAN:				_hotkey[i] = 'G';			break;
		case COMMAND_UNIT_DEVOURER:				_hotkey[i] = 'D';			break;
		case COMMAND_UNIT_INFESTEDTERRAN:		_hotkey[i] = 'I';			break;


			//UPGRADE
		case COMMAND_UPGRADE_ZERG_MELEEATTACKS:				_hotkey[i] = 'M';	break;	//���� �������� ���� ����
		case COMMAND_UPGRADE_ZERG_MISSILEATTACKS:			_hotkey[i] = 'A';	break;	//���� �������� ���Ÿ� ����
		case COMMAND_UPGRADE_ZERG_CARAPACE:					_hotkey[i] = 'C';	break;	//���� �������� ����
		case COMMAND_UPGRADE_ZERG_FLYERATTACKS:				_hotkey[i] = 'A';	break;	//���� �������� ����
		case COMMAND_UPGRADE_ZERG_FLYERCARAPACE:			_hotkey[i] = 'C';	break;	//���� �������� ����

			//EVOLUTION
		case COMMAND_EVOLUTION_ZERG_BURROW:					_hotkey[i] = 'B';	break;	//���� ������ ����
		case COMMAND_EVOLUTION_ZERG_METABOLICK_BOOST:		_hotkey[i] = 'M';	break;	//���۸� �̼Ӿ�
		case COMMAND_EVOLUTION_ZERG_ADRENAL_GLANDS:			_hotkey[i] = 'A';	break;	//���۸� �Ƶ巹����
		case COMMAND_EVOLUTION_ZERG_VECTRAL_SACS:			_hotkey[i] = 'V';	break;	//�����ε� ���۾�
		case COMMAND_EVOLUTION_ZERG_ANTENNAE:				_hotkey[i] = 'A';	break;	//�����ε� �þ߾�
		case COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:	_hotkey[i] = 'P';	break;	//�����ε� �̼Ӿ�
		case COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS:		_hotkey[i] = 'M';	break;	//����� �̼Ӿ�
		case COMMAND_EVOLUTION_ZERG_GROOVED_SPINES:			_hotkey[i] = 'G';	break;	//����� �����Ÿ���
		case COMMAND_EVOLUTION_ZERG_LURKER_ASPECT:			_hotkey[i] = 'L';	break;	//��Ŀ ����
		case COMMAND_EVOLUTION_ZERG_SPAWN_BROODLING:		_hotkey[i] = 'B';	break;	//�� ���帵 ����
		case COMMAND_EVOLUTION_ZERG_ENSNARE:				_hotkey[i] = 'E';	break;	//�� �ν��׾� ����
		case COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS:			_hotkey[i] = 'G';	break;	//�� ������
		case COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:		_hotkey[i] = 'A';	break;	//��Ʈ�� �̼Ӿ�
		case COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING:		_hotkey[i] = 'C';	break;	//��Ʈ�� ���(+2)
		case COMMAND_EVOLUTION_ZERG_PLAGUE:					_hotkey[i] = 'G';	break;	//�����Ϸ� �÷��̱�
		case COMMAND_EVOLUTION_ZERG_CONSUME:				_hotkey[i] = 'C';	break;	//�����Ϸ� ����
		case COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE:		_hotkey[i] = 'M';	break;	//�����Ϸ� ������

		default:								
			_hotkey[i] = 0;			
			break;

		}										
	}

	return S_OK;
}
void hotkeys::release(void)
{

}
void hotkeys::update(void) 
{

}
void hotkeys::render(void) 
{

}
