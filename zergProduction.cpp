#include "stdafx.h"
#include "zergProduction.h"

tagProduction zergProduction::_zuProduction[UNITNUM_ZERG_MAX];
tagProduction zergProduction::_zbProduction[BUILDINGNUM_ZERG_MAX];

zergProduction::zergProduction(bool initInfo)
{
	if (!initInfo) return;

	for (int i = 0; i < UNITNUM_ZERG_MAX; i++)
	{
		switch (i)
		{
			case UNITNUM_ZERG_LARVA: 
				break;
			case UNITNUM_ZERG_ZERGEGG: 
				break;
			case UNITNUM_ZERG_DRONE: 
				_zuProduction[i].costMinerals = 50;		//소모 미네랄
				_zuProduction[i].costGas = 0;			//소모 가스
				_zuProduction[i].control = 1.0f;		//인구수
				_zuProduction[i].buildTime = 20.0f;		//빌드시간
				_zuProduction[i].hotKey = 'D';			//단축키
				break;
			case UNITNUM_ZERG_ZERGLING: 
				break;
			case UNITNUM_ZERG_HYDRALISK: 
				break;
			case UNITNUM_ZERG_LURKER: 
				break;
			case UNITNUM_ZERG_LURKEREGG: 
				break;
			case UNITNUM_ZERG_ULTRALISK: 
				break;
			case UNITNUM_ZERG_BROODLING: 
				break;
			case UNITNUM_ZERG_DEFILER: 
				break;
			case UNITNUM_ZERG_INFESTEDTERRAN: 
				break;
			case UNITNUM_ZERG_OVERLORD: 
				break;
			case UNITNUM_ZERG_MUTALISK: 
				break;
			case UNITNUM_ZERG_SCOURGE: 
				break;
			case UNITNUM_ZERG_QUEEN: 
				break;
			case UNITNUM_ZERG_COCOON: 
				break;
			case UNITNUM_ZERG_GUADIAN: 
				break;
			case UNITNUM_ZERG_DEVOURER: 
				break;
		}
	}

	for (int i = 0; i < BUILDINGNUM_ZERG_MAX; i++)
	{
		switch (i)
		{
			//BUILD1
			case BUILDINGNUM_ZERG_HATCHERY:
				break;
			case BUILDINGNUM_ZERG_LAIR:
				break;
			case BUILDINGNUM_ZERG_HIVE:
				break;
			
			case BUILDINGNUM_ZERG_CREEPCOLONY:
				break;
			case BUILDINGNUM_ZERG_SUNKENCOLONY:
				break;
			case BUILDINGNUM_ZERG_SPORECOLONY:
				break;

			case BUILDINGNUM_ZERG_EXTRACTOR:
				break;
			case BUILDINGNUM_ZERG_SPAWNINGPOOL:
				break;
			case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:
				break;
			case BUILDINGNUM_ZERG_HYDRALISKDEN:
				break;
			
			//BUILD2
			case BUILDINGNUM_ZERG_SPIRE:
				break;
			case BUILDINGNUM_ZERG_GREATERSPIRE:
				break;
			case BUILDINGNUM_ZERG_QUEENSNEST:
				break;
			case BUILDINGNUM_ZERG_NYDUSCANAL:
				break;
			case BUILDINGNUM_ZERG_ULTRALISKCAVERN:
				break;
			case BUILDINGNUM_ZERG_DEFILERMOUND:
				break;
			
			//SPECIAL
			case BUILDINGNUM_ZERG_INFESTEDCOMMANDCENTER:
				break;
		}
	}
}


zergProduction::zergProduction()
{
}


zergProduction::~zergProduction()
{

}


//tagProduction zergProduction::getZUProduction(UNITNUM_ZERG num)
//{
//	return _zuProduction[num]; 
//}