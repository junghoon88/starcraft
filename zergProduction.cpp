#include "stdafx.h"
#include "zergProduction.h"

tagProduction zergProduction::_zuProduction[UNITNUM_ZERG_MAX];

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
				_zuProduction[i].costMinerals = 50;		//�Ҹ� �̳׶�
				_zuProduction[i].costGas = 0;			//�Ҹ� ����
				_zuProduction[i].control = 1.0f;		//�α���
				_zuProduction[i].buildTime = 20.0f;		//����ð�
				_zuProduction[i].hotKey = 'D';			//����Ű
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