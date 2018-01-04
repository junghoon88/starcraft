#include "stdafx.h"
#include "zergProductionInfo.h"

tagProduction zergProductionInfo::_zuProduction[UNITNUM_ZERG_MAX];
tagProduction zergProductionInfo::_zbProduction[BUILDINGNUM_ZERG_MAX];

zergProductionInfo::zergProductionInfo(bool initInfo)
{
	ZeroMemory(&_zuProduction, sizeof(tagProduction) * UNITNUM_ZERG_MAX);
	ZeroMemory(&_zbProduction, sizeof(tagProduction) * BUILDINGNUM_ZERG_MAX);

	if (!initInfo) return;

	for (int i = 0; i < UNITNUM_ZERG_MAX; i++)
	{
		switch (i)
		{
			case UNITNUM_ZERG_LARVA: 
				_zuProduction[i].buildTime = 15.0f;		//빌드시간
				break;
			case UNITNUM_ZERG_ZERGEGG: 
				break;
			case UNITNUM_ZERG_DRONE: 
				_zuProduction[i].costMinerals = 50;		//소모 미네랄
				_zuProduction[i].costGas = 0;			//소모 가스
				_zuProduction[i].control = 1.0f;		//인구수
				_zuProduction[i].buildTime = 20.0f;		//빌드시간
				break;
			case UNITNUM_ZERG_ZERGLING: 
				_zuProduction[i].costMinerals = 50;		//소모 미네랄
				_zuProduction[i].costGas = 0;			//소모 가스
				_zuProduction[i].control = 1.0f;		//인구수
				_zuProduction[i].buildTime = 28.0f;		//빌드시간
				break;
			case UNITNUM_ZERG_HYDRALISK: 
				_zuProduction[i].costMinerals = 75;		//소모 미네랄
				_zuProduction[i].costGas = 25;			//소모 가스
				_zuProduction[i].control = 1.0f;		//인구수
				_zuProduction[i].buildTime = 28.0f;		//빌드시간
				break;
			case UNITNUM_ZERG_LURKER: 
				_zuProduction[i].costMinerals = 50;		//소모 미네랄
				_zuProduction[i].costGas = 100;			//소모 가스
				_zuProduction[i].control = 2.0f;		//인구수
				_zuProduction[i].buildTime = 40.0;		//빌드시간
				break;
			case UNITNUM_ZERG_LURKEREGG: 
				break;
			case UNITNUM_ZERG_ULTRALISK: 
				_zuProduction[i].costMinerals = 200;	//소모 미네랄
				_zuProduction[i].costGas = 200;			//소모 가스
				_zuProduction[i].control = 4.0f;		//인구수
				_zuProduction[i].buildTime = 60.0;		//빌드시간
				break;
			case UNITNUM_ZERG_BROODLING: 
				break;
			case UNITNUM_ZERG_DEFILER: 
				_zuProduction[i].costMinerals = 50;		//소모 미네랄
				_zuProduction[i].costGas = 150;			//소모 가스
				_zuProduction[i].control = 2.0f;		//인구수
				_zuProduction[i].buildTime = 50.0;		//빌드시간
				break;
			case UNITNUM_ZERG_INFESTEDTERRAN: 
				_zuProduction[i].costMinerals = 100;	//소모 미네랄
				_zuProduction[i].costGas = 50;			//소모 가스
				_zuProduction[i].control = 1.0f;		//인구수
				_zuProduction[i].buildTime = 40.0;		//빌드시간
				break;
			case UNITNUM_ZERG_OVERLORD: 
				_zuProduction[i].costMinerals = 100;	//소모 미네랄
				_zuProduction[i].costGas = 0;			//소모 가스
				_zuProduction[i].control = 0.0f;		//인구수
				_zuProduction[i].buildTime = 40.0;		//빌드시간
				break;
			case UNITNUM_ZERG_MUTALISK: 
				_zuProduction[i].costMinerals = 100;	//소모 미네랄
				_zuProduction[i].costGas = 100;			//소모 가스
				_zuProduction[i].control = 2.0f;		//인구수
				_zuProduction[i].buildTime = 40.0;		//빌드시간
				break;
			case UNITNUM_ZERG_SCOURGE: 
				_zuProduction[i].costMinerals = 25;		//소모 미네랄
				_zuProduction[i].costGas = 75;			//소모 가스
				_zuProduction[i].control = 1.0f;		//인구수
				_zuProduction[i].buildTime = 30.0;		//빌드시간
				break;
			case UNITNUM_ZERG_QUEEN: 
				_zuProduction[i].costMinerals = 100;	//소모 미네랄
				_zuProduction[i].costGas = 100;			//소모 가스
				_zuProduction[i].control = 2.0f;		//인구수
				_zuProduction[i].buildTime = 50.0;		//빌드시간
				break;
			case UNITNUM_ZERG_COCOON: 
				break;
			case UNITNUM_ZERG_GUADIAN: 
				_zuProduction[i].costMinerals = 50;		//소모 미네랄
				_zuProduction[i].costGas = 100;			//소모 가스
				_zuProduction[i].control = 2.0f;		//인구수
				_zuProduction[i].buildTime = 40.0;		//빌드시간
				break;
			case UNITNUM_ZERG_DEVOURER: 
				_zuProduction[i].costMinerals = 150;	//소모 미네랄
				_zuProduction[i].costGas = 50;			//소모 가스
				_zuProduction[i].control = 2.0f;		//인구수
				_zuProduction[i].buildTime = 40.0;		//빌드시간
				break;
		}
	}

	for (int i = 0; i < BUILDINGNUM_ZERG_MAX; i++)
	{
		switch (i)
		{
			//BUILD1
			case BUILDINGNUM_ZERG_HATCHERY:
				_zbProduction[i].costMinerals = 300;	//소모 미네랄
				_zbProduction[i].costGas = 0;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 120.0f;	//빌드시간
				break;
			case BUILDINGNUM_ZERG_LAIR:
				_zbProduction[i].costMinerals = 150;	//소모 미네랄
				_zbProduction[i].costGas = 100;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 100.0f;	//빌드시간
				break;
			case BUILDINGNUM_ZERG_HIVE:
				_zbProduction[i].costMinerals = 200;	//소모 미네랄
				_zbProduction[i].costGas = 150;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 120.0f;	//빌드시간
				break;
			
			case BUILDINGNUM_ZERG_CREEPCOLONY:
				_zbProduction[i].costMinerals = 75;		//소모 미네랄
				_zbProduction[i].costGas = 0;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 20.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_SUNKENCOLONY:
				_zbProduction[i].costMinerals = 50;		//소모 미네랄
				_zbProduction[i].costGas = 0;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 20.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_SPORECOLONY:
				_zbProduction[i].costMinerals = 50;		//소모 미네랄
				_zbProduction[i].costGas = 0;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 20.0f;		//빌드시간
				break;

			case BUILDINGNUM_ZERG_EXTRACTOR:
				_zbProduction[i].costMinerals = 50;		//소모 미네랄
				_zbProduction[i].costGas = 0;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 40.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_SPAWNINGPOOL:
				_zbProduction[i].costMinerals = 200;	//소모 미네랄
				_zbProduction[i].costGas = 0;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 80.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:
				_zbProduction[i].costMinerals = 75;		//소모 미네랄
				_zbProduction[i].costGas = 0;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 40.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_HYDRALISKDEN:
				_zbProduction[i].costMinerals = 100;	//소모 미네랄
				_zbProduction[i].costGas = 50;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 40.0f;		//빌드시간
				break;
			
			//BUILD2
			case BUILDINGNUM_ZERG_SPIRE:
				_zbProduction[i].costMinerals = 200;	//소모 미네랄
				_zbProduction[i].costGas = 150;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 120.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_GREATERSPIRE:
				_zbProduction[i].costMinerals = 100;	//소모 미네랄
				_zbProduction[i].costGas = 150;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 120.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_QUEENSNEST:
				_zbProduction[i].costMinerals = 150;	//소모 미네랄
				_zbProduction[i].costGas = 100;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 60.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_NYDUSCANAL:
				_zbProduction[i].costMinerals = 150;	//소모 미네랄
				_zbProduction[i].costGas = 0;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 40.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_ULTRALISKCAVERN:
				_zbProduction[i].costMinerals = 150;	//소모 미네랄
				_zbProduction[i].costGas = 200;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 80.0f;		//빌드시간
				break;
			case BUILDINGNUM_ZERG_DEFILERMOUND:
				_zbProduction[i].costMinerals = 100;	//소모 미네랄
				_zbProduction[i].costGas = 100;			//소모 가스
				_zbProduction[i].control = 0.0f;		//인구수
				_zbProduction[i].buildTime = 60.0f;		//빌드시간
				break;
			
			//SPECIAL
			case BUILDINGNUM_ZERG_INFESTEDCOMMANDCENTER:
				break;
		}
	}
}


zergProductionInfo::zergProductionInfo()
{
}


zergProductionInfo::~zergProductionInfo()
{

}


