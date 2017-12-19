#include "stdafx.h"
#include "zergUpgrade.h"


zergUpgrade::zergUpgrade()
{
	for (int i = 0; i < UPGRADE_ZERG_MAX; i++)
	{
		_upgrade[i].isProcessing = false;
		_upgrade[i].complete = false;

		switch (i)
		{
		case UPGRADE_ZERG_CARAPACE:
			_stprintf(_upgrade[i].name, L"저그 방어력");
			_upgrade[i].level = 0;		//레벨
			_upgrade[i].maxLevel = 3;	//맥스레벨

			for (int j = 0; j < _upgrade[i].maxLevel; j++)
			{
				tagUpgradeCost cost;
				cost.level = j;
				cost.mineral = 100;
				cost.gas = 100;
				cost.duration = 10.0f;

				_upgrade[i].vCost.push_back(cost);
			}
			break;
		case UPGRADE_ZERG_FLYERCARAPACE:
			break;
		case UPGRADE_ZERG_MELEEATTACKS:
			break;
		case UPGRADE_ZERG_MISSILEATTACKS:
			break;
		case UPGRADE_ZERG_FLYERATTACKS:
			break;
		}
	}

	for (int i = 0; i < EVOLUTION_ZERG_MAX; i++)
	{
		_evolution[i].isProcessing = false;
		_evolution[i].complete = false;

		switch (i)
		{
		case EVOLUTION_ZERG_VECTRAL_SACS:
			break;
		case EVOLUTION_ZERG_ANTENNAE:
			break;
		case EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:
			break;
		case EVOLUTION_ZERG_METABOLICK_BOOST:
			break;
		case EVOLUTION_ZERG_ADRENAL_GLANDS:
			break;
		case EVOLUTION_ZERG_MUSCULAR_AUGMENTS:
			break;
		case EVOLUTION_ZERG_GROOVED_SPINES:
			break;
		case EVOLUTION_ZERG_GAMETE_MEIOSIS:
			break;
		case EVOLUTION_ZERG_METASYNAPTIC_NODE:
			break;
		case EVOLUTION_ZERG_CHITINOUS_PLATING:
			break;
		case EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:
			break;
		}
	}
}


zergUpgrade::~zergUpgrade()
{
}
