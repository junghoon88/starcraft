#include "stdafx.h"
#include "zergUpgrade.h"


zergUpgrade::zergUpgrade()
{
	ZeroMemory(&_upgrade,	sizeof(tagUpgrade)*UPGRADE_ZERG_MAX);
	ZeroMemory(&_evolution, sizeof(tagEvolution)*EVOLUTION_ZERG_MAX);

	for (int i = 0; i < UPGRADE_ZERG_MAX; i++)
	{
		_upgrade[i].isProcessing = false;
		_upgrade[i].complete = false;

		switch (i)
		{
		case UPGRADE_ZERG_MELEEATTACKS:
			_stprintf(_upgrade[i].name, L"Melee Attacks");
			_upgrade[i].level = 0;
			_upgrade[i].maxLevel = 3;

			for (int j = 0; j < _upgrade[i].maxLevel; j++)
			{
				tagUpgradeCost cost;
				cost.level = j;
				cost.mineral = 100 + j * 50;
				cost.gas = 100 + j * 50;
				cost.duration = 266.0f + j * 32.0f;

				_upgrade[i].vCost.push_back(cost);
			}
			break;
		case UPGRADE_ZERG_MISSILEATTACKS:
			_stprintf(_upgrade[i].name, L"Missile Attacks");
			_upgrade[i].level = 0;
			_upgrade[i].maxLevel = 3;

			for (int j = 0; j < _upgrade[i].maxLevel; j++)
			{
				tagUpgradeCost cost;
				cost.level = j;
				cost.mineral = 100 + j * 50;
				cost.gas = 100 + j * 50;
				cost.duration = 266.0f + j * 32.0f;

				_upgrade[i].vCost.push_back(cost);
			}
			break;
		case UPGRADE_ZERG_CARAPACE:
			_stprintf(_upgrade[i].name, L"Carapace");
			_upgrade[i].level = 0;		
			_upgrade[i].maxLevel = 3;	

			for (int j = 0; j < _upgrade[i].maxLevel; j++)
			{
				tagUpgradeCost cost;
				cost.level = j;
				cost.mineral = 150 + j * 75;
				cost.gas = 150 + j * 75;
				cost.duration = 266.0f + j * 32.0f;

				_upgrade[i].vCost.push_back(cost);
			}
			break;
		case UPGRADE_ZERG_FLYERATTACKS:
			_stprintf(_upgrade[i].name, L"Flyer Attacks");
			_upgrade[i].level = 0;
			_upgrade[i].maxLevel = 3;

			for (int j = 0; j < _upgrade[i].maxLevel; j++)
			{
				tagUpgradeCost cost;
				cost.level = j;
				cost.mineral = 100 + j * 75;
				cost.gas = 100 + j * 75;
				cost.duration = 266.0f + j * 32.0f;

				_upgrade[i].vCost.push_back(cost);
			}
			break;
		case UPGRADE_ZERG_FLYERCARAPACE:
			_stprintf(_upgrade[i].name, L"Flyer Carapace");
			_upgrade[i].level = 0;
			_upgrade[i].maxLevel = 3;

			for (int j = 0; j < _upgrade[i].maxLevel; j++)
			{
				tagUpgradeCost cost;
				cost.level = j;
				cost.mineral = 150 + j * 75;
				cost.gas = 150 + j * 75;
				cost.duration = 266.0f + j * 32.0f;

				_upgrade[i].vCost.push_back(cost);
			}
			break;
		}
	}

	for (int i = 0; i < EVOLUTION_ZERG_MAX; i++)
	{
		_evolution[i].isProcessing = false;
		_evolution[i].complete = false;

		switch (i)
		{
		case EVOLUTION_ZERG_BURROW:			//저그 버러우 업글
			_stprintf(_evolution[i].name, L"Burrow");
			_evolution[i].cost.mineral	= 100;
			_evolution[i].cost.gas		= 100;
			_evolution[i].cost.duration = 80.0f;
			break;
		case EVOLUTION_ZERG_METABOLICK_BOOST:		//저글링 이속업
			_stprintf(_evolution[i].name, L"Metabolic Boost");
			_evolution[i].cost.mineral	= 100;
			_evolution[i].cost.gas		= 100;
			_evolution[i].cost.duration = 100.0f;
			break;
		case EVOLUTION_ZERG_ADRENAL_GLANDS:			//저글링 아드레날린
			_stprintf(_evolution[i].name, L"Adrenal Glands");
			_evolution[i].cost.mineral	= 200;
			_evolution[i].cost.gas		= 200;
			_evolution[i].cost.duration = 100.0f;
			break;
		case EVOLUTION_ZERG_VECTRAL_SACS:			//오버로드 수송업
			_stprintf(_evolution[i].name, L"Ventral Sacs");
			_evolution[i].cost.mineral	= 200;
			_evolution[i].cost.gas		= 200;
			_evolution[i].cost.duration = 160.0f;
			break;
		case EVOLUTION_ZERG_ANTENNAE:				//오버로드 시야업
			_stprintf(_evolution[i].name, L"Antennae");
			_evolution[i].cost.mineral	= 150;
			_evolution[i].cost.gas		= 150;
			_evolution[i].cost.duration = 133.0f;
			break;
		case EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:	//오버로드 이속업
			_stprintf(_evolution[i].name, L"Pneumatized Carapace");
			_evolution[i].cost.mineral	= 150;
			_evolution[i].cost.gas		= 150;
			_evolution[i].cost.duration = 133.0f;
			break;
		case EVOLUTION_ZERG_MUSCULAR_AUGMENTS:		//히드라 이속업
			_stprintf(_evolution[i].name, L"Muscular Augments");
			_evolution[i].cost.mineral	= 150;
			_evolution[i].cost.gas		= 150;
			_evolution[i].cost.duration = 100.0f;
			break;
		case EVOLUTION_ZERG_GROOVED_SPINES:			//히드라 사정거리업
			_stprintf(_evolution[i].name, L"Grooved Spines");
			_evolution[i].cost.mineral	= 150;
			_evolution[i].cost.gas		= 150;
			_evolution[i].cost.duration = 100.0f;
			break;
		case EVOLUTION_ZERG_LURKER_ASPECT:	//럴커 업글
			_stprintf(_evolution[i].name, L"Lurker Morph");
			_evolution[i].cost.mineral	= 200;
			_evolution[i].cost.gas		= 200;
			_evolution[i].cost.duration = 120.0f;
			break;
		case EVOLUTION_ZERG_SPAWN_BROODLING:	//퀸 브루드링 업글
			_stprintf(_evolution[i].name, L"Spawn Broodling");
			_evolution[i].cost.mineral	= 100;
			_evolution[i].cost.gas		= 100;
			_evolution[i].cost.duration = 80.0f;
			break;
		case EVOLUTION_ZERG_ENSNARE:			//퀸 인스테어 업글
			_stprintf(_evolution[i].name, L"Ensnare");
			_evolution[i].cost.mineral	= 100;
			_evolution[i].cost.gas		= 100;
			_evolution[i].cost.duration = 80.0f;
			break;
		case EVOLUTION_ZERG_GAMETE_MEIOSIS:			//퀸 마나업
			_stprintf(_evolution[i].name, L"Gamete Meiosis");
			_evolution[i].cost.mineral	= 150;
			_evolution[i].cost.gas		= 150;
			_evolution[i].cost.duration = 166.0f;
			break;
		case EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:		//울트라 이속업
			_stprintf(_evolution[i].name, L"Anabolic Synthesis");
			_evolution[i].cost.mineral	= 200;
			_evolution[i].cost.gas		= 200;
			_evolution[i].cost.duration = 133.0f;
			break;
		case EVOLUTION_ZERG_CHITINOUS_PLATING:		//울트라 방업(+2)
			_stprintf(_evolution[i].name, L"Chitinous Plating");
			_evolution[i].cost.mineral	= 150;
			_evolution[i].cost.gas		= 150;
			_evolution[i].cost.duration = 133.0f;
			break;
		case EVOLUTION_ZERG_PLAGUE:			//디파일러 플레이그
			_stprintf(_evolution[i].name, L"Plague");
			_evolution[i].cost.mineral	= 200;
			_evolution[i].cost.gas		= 200;
			_evolution[i].cost.duration = 100.0f;
			break;
		case EVOLUTION_ZERG_CONSUME:			//디파일러 컨슘
			_stprintf(_evolution[i].name, L"Consume");
			_evolution[i].cost.mineral	= 100;
			_evolution[i].cost.gas		= 100;
			_evolution[i].cost.duration = 100.0f;
			break;
		case EVOLUTION_ZERG_METASYNAPTIC_NODE:		//디파일러 마나업
			_stprintf(_evolution[i].name, L"Metasynaptic Node");
			_evolution[i].cost.mineral	= 150;
			_evolution[i].cost.gas		= 150;
			_evolution[i].cost.duration = 166.0f;
			break;
		}
	}
}


zergUpgrade::~zergUpgrade()
{
}

void zergUpgrade::upgradeComplete(UPGRADE_ZERG num)
{
	_upgrade[num].isProcessing = false;

	_upgrade[num].level += 1;

	if (_upgrade[num].level == _upgrade[num].maxLevel)
	{
		_upgrade[num].complete = true;
	}
}
void zergUpgrade::evolutionComplete(EVOLUTION_ZERG num)
{
	_evolution[num].isProcessing = false;
	_evolution[num].complete = true;
}
