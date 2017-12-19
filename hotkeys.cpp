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
		case COMMAND_BUILD_HYDRALISKDEN:		_hotkey[i] = 'H';			break;
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
