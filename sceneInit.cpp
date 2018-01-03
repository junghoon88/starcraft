#include "stdafx.h"
#include "sceneInit.h"
#include "tileNode.h"


sceneInit::sceneInit()
	: _loading(NULL)
{
}


sceneInit::~sceneInit()
{
}

HRESULT sceneInit::init(void)
{
	_loading = new loading;
	_loading->init();


	initImage();
	initSound();


	return S_OK;
}


void sceneInit::release(void)
{
	_loading->release();
	SAFE_DELETE(_loading);
}

void sceneInit::update(void)
{
	if (_loading->loadingImageDone())
	{
		_loading->update();
		SCENEMANAGER->changeScene(L"선택씬");
	}
	else
	{
		_loading->update();
	}
}

void sceneInit::render(void)
{
	_loading->render();
}

void sceneInit::initImage(void)
{
	_loading->loadFrameImage(L"버튼1", L"image/button1.bmp", 100, 60, 1, 2);
	_loading->loadFrameImage(L"버튼2", L"image/button2.bmp", 123, 29, 1, 1);

	initImageNeutralResource();

	initImageMaptoolTiles();
	initImageGamemapTiles();

	initImageInterface();

	initImageZergUnits();
	initImageZergBuildings();
}

void sceneInit::initSound(void)
{

}

void sceneInit::initImageNeutralResource(void)
{
	_loading->loadFrameImage(L"NeutralResource-Mineral1", L"image/neutral/min01.bmp", 64, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"NeutralResource-Mineral2", L"image/neutral/min02.bmp", 64, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"NeutralResource-Mineral3", L"image/neutral/min03.bmp", 64, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->loadImage(L"NeutralResource-Gas", L"image/neutral/gas.bmp", TILESIZE * 4, TILESIZE * 2, true, RGB(255, 0, 255));
}

void sceneInit::initImageMaptoolTiles(void)
{
	TCHAR strKey[128] = L"";
	TCHAR strFile[128] = L"";


	//terrain-Dirt
	_loading->loadFrameImage(L"maptool-terrain-Dirt", L"image/maptool/tiles/terrain-Dirt/terrainDirt.bmp", 768, 640, 24, 20);

	//terrain-HighDirt
	_loading->loadFrameImage(L"maptool-terrain-HighDirt", L"image/maptool/tiles/terrain-HighDirt/IDLE3x2.bmp", TILESIZE*3, TILESIZE*2, 3, 2);

	_loading->loadFrameImage(L"maptool-terrain-HighDirt-LD", L"image/maptool/tiles/terrain-HighDirt/LD2x3.bmp", TILESIZE * 2, TILESIZE * 3, 2, 3);
	_loading->loadFrameImage(L"maptool-terrain-HighDirt-LF", L"image/maptool/tiles/terrain-HighDirt/LF2x3.bmp", TILESIZE * 2, TILESIZE * 3, 2, 3);
	_loading->loadFrameImage(L"maptool-terrain-HighDirt-LU", L"image/maptool/tiles/terrain-HighDirt/LU2x2.bmp", TILESIZE * 2, TILESIZE * 2, 2, 2);

	_loading->loadFrameImage(L"maptool-terrain-HighDirt-RD", L"image/maptool/tiles/terrain-HighDirt/RD2x3.bmp", TILESIZE * 2, TILESIZE * 3, 2, 3);
	_loading->loadFrameImage(L"maptool-terrain-HighDirt-RG", L"image/maptool/tiles/terrain-HighDirt/RG2x3.bmp", TILESIZE * 2, TILESIZE * 3, 2, 3);
	_loading->loadFrameImage(L"maptool-terrain-HighDirt-RU", L"image/maptool/tiles/terrain-HighDirt/RU2x2.bmp", TILESIZE * 2, TILESIZE * 2, 2, 2);

	//terrain-Water
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Water-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Water/%02d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, TILESIZE, TILESIZE, 1, 1);
	}

	//icon
	_loading->loadImage(L"maptool-icon-Mineral",	L"image/maptool/iconMineral.bmp",		TILESIZE, TILESIZE);
	_loading->loadImage(L"maptool-icon-Gas",		L"image/maptool/iconGas.bmp",			TILESIZE, TILESIZE);
	_loading->loadImage(L"maptool-icon-LocationP1", L"image/maptool/iconLocationP1.bmp",	TILESIZE, TILESIZE);
	_loading->loadImage(L"maptool-icon-LocationP2", L"image/maptool/iconLocationP2.bmp",	TILESIZE, TILESIZE);
	_loading->loadImage(L"maptool-icon-iconEraser", L"image/maptool/iconEraser.bmp",		TILESIZE, TILESIZE);

	//object
	_loading->loadImage(L"maptool-object-LocationP1", L"image/maptool/location-p1.bmp", TILESIZE * 4, TILESIZE * 3, true, RGB(255, 0, 255));
	_loading->loadImage(L"maptool-object-LocationP2", L"image/maptool/location-p2.bmp", TILESIZE * 4, TILESIZE * 3, true, RGB(255, 0, 255));

	_loading->loadImage(L"maptool-object-enableTile",  L"image/maptool/tiles/enableTile.bmp", TILESIZE, TILESIZE, false, RGB(0, 0, 0), true);
	_loading->loadImage(L"maptool-object-disableTile", L"image/maptool/tiles/disableTile.bmp", TILESIZE, TILESIZE, false, RGB(0, 0, 0), true);

}

void sceneInit::initImageGamemapTiles(void)
{
	TCHAR strKey[128] = L"";
	TCHAR strFile[128] = L"";

	_loading->loadImage(L"gamemap-fog", L"image/gamemap/fog.bmp", TILESIZE, TILESIZE, false, RGB(0, 0, 0), true);


}

void sceneInit::initImageInterface(void)
{
	//icon
	_loading->loadImage(L"interface-iconMineral",	L"image/interface/iconMineral.bmp", 14, 14);
	_loading->loadImage(L"interface-iconGas",		L"image/interface/iconGas.bmp",		14, 14);
	_loading->loadImage(L"interface-iconControl",	L"image/interface/iconControl.bmp", 14, 14);

	//progressbar
	_loading->loadImage(L"frontBarMutating",	L"image/interface/progressbarF.bmp", 107, 9, true, RGB(255, 0, 255));
	_loading->loadImage(L"backBarMutating",		L"image/interface/progressbarB.bmp", 107, 9);

	//cursor
	_loading->loadFrameImage(L"cursor-Idle",			L"image/interface/cursor-Idle.bmp",			100, 21, 5, 1, true, RGB(255, 0, 255));
	_loading->loadImage(L"cursor-Dragging",				L"image/interface/cursor-Dragging.bmp",		 18, 22, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-onme",			L"image/interface/cursor-onme.bmp",			574, 41, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-onneutral",		L"image/interface/cursor-onneutral.bmp",	574, 41, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-onenemy",			L"image/interface/cursor-onenemy.bmp",		574, 41, 14, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage(L"cursor-FocusToMe",		L"image/interface/cursor-FocusToMe.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-FocusToNeutral",	L"image/interface/cursor-FocusToNeutral.bmp",	82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-FocusToEnemy",	L"image/interface/cursor-FocusToEnemy.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage(L"cursor-MoveDN",			L"image/interface/cursor-MoveDN.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-MoveUP",			L"image/interface/cursor-MoveUP.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-MoveLF",			L"image/interface/cursor-MoveLF.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-MoveRG",			L"image/interface/cursor-MoveRG.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-MoveLU",			L"image/interface/cursor-MoveLU.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-MoveLD",			L"image/interface/cursor-MoveLD.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-MoveRU",			L"image/interface/cursor-MoveRU.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-MoveRD",			L"image/interface/cursor-MoveRD.bmp",		82, 41, 2, 1, true, RGB(255, 0, 255));

	//interface
	_loading->loadImage(L"interfaceZ", L"image/interface/interface-Z.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage(L"interfaceT", L"image/interface/interface-T.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage(L"interfaceP", L"image/interface/interface-P.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	
	////commands
	//COMMON
	_loading->loadFrameImage(L"command-esc",					  L"image/interface/command/esc.bmp",						 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-move",					  L"image/interface/command/move.bmp",						 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-stop",					  L"image/interface/command/stop.bmp",						 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-attack",					  L"image/interface/command/attack.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-patrol",					  L"image/interface/command/patrol.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-hold",					  L"image/interface/command/hold.bmp",						 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-gather",					  L"image/interface/command/gather.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-returncargo",			  L"image/interface/command/returncargo.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build1",					  L"image/interface/command/build1.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build2",					  L"image/interface/command/build2.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));

	_loading->loadFrameImage(L"command-select_larva",			  L"image/interface/command/select_larva.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-set_rally_point",		  L"image/interface/command/set_rally_point.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));

																										 
	//ZERG
	_loading->loadFrameImage(L"command-burrow",					  L"image/interface/command/burrow.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unburrow",				  L"image/interface/command/unburrow.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-infest",					  L"image/interface/command/infest.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-parasite",				  L"image/interface/command/parasite.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0)); 

	_loading->loadFrameImage(L"command-broodring",				  L"image/interface/command/broodring.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-ensnare",				  L"image/interface/command/ensnare.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-consume",				  L"image/interface/command/consume.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-darkswarm",				  L"image/interface/command/darkswarm.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-plague",					  L"image/interface/command/plague.bmp",					 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
																										 
	//BUILD1																							 
	_loading->loadFrameImage(L"command-build_hatchery",			  L"image/interface/command/build_hatchery.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_lair",				  L"image/interface/command/build_lair.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_hive",				  L"image/interface/command/build_hive.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_creepcolony",		  L"image/interface/command/build_creepcolony.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_sunkencolony",		  L"image/interface/command/build_sunkencolony.bmp",		 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_sporecolony",		  L"image/interface/command/build_sporecolony.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_extractor",		  L"image/interface/command/build_extractor.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_spawningpool",		  L"image/interface/command/build_spawningpool.bmp",		 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_evolutionchamber",	  L"image/interface/command/build_evolutionchamber.bmp",	 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_hydraliskden",		  L"image/interface/command/build_hydraliskden.bmp",		 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
																										 
	//BUILD2																							 
	_loading->loadFrameImage(L"command-build_spire",			  L"image/interface/command/build_spire.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_greaterspire",		  L"image/interface/command/build_greaterspire.bmp",		 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_queensnest",		  L"image/interface/command/build_queensnest.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_nyduscanal",		  L"image/interface/command/build_nyduscanal.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_ultraliskcavern",	  L"image/interface/command/build_ultraliskcavern.bmp",		 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-build_defilermound",		  L"image/interface/command/build_defilermound.bmp",		 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
																										 
	//UNIT																								 
	_loading->loadFrameImage(L"command-unit_drone",				  L"image/interface/command/unit_drone.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_zergling",			  L"image/interface/command/unit_zergling.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_overlord",			  L"image/interface/command/unit_overlord.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_hydralisk",			  L"image/interface/command/unit_hydralisk.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_mutalisk",			  L"image/interface/command/unit_mutalisk.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_scourge",			  L"image/interface/command/unit_scourge.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_queen",				  L"image/interface/command/unit_queen.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_ultralisk",			  L"image/interface/command/unit_ultralisk.bmp",			 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_defiler",			  L"image/interface/command/unit_defiler.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	//UNIT2																								 
	_loading->loadFrameImage(L"command-unit_lurker",			  L"image/interface/command/unit_lurker.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_guadian",			  L"image/interface/command/unit_guadian.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_devourer",			  L"image/interface/command/unit_devourer.bmp",				 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));
	_loading->loadFrameImage(L"command-unit_infestedterran",	  L"image/interface/command/unit_infestedterran.bmp",		 COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));

	//UPGRADE
	_loading->loadFrameImage(L"command-upgrade_zerg_meleeattacks",					L"image/interface/command/upgrade_zerg_meleeattacks.bmp",				COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//저그 지상유닛 근접 공격
	_loading->loadFrameImage(L"command-upgrade_zerg_missileattacks",				L"image/interface/command/upgrade_zerg_missileattacks.bmp",				COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//저그 지상유닛 원거리 공격
	_loading->loadFrameImage(L"command-upgrade_zerg_carapace",						L"image/interface/command/upgrade_zerg_carapace.bmp",					COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//저그 지상유닛 방어력
	_loading->loadFrameImage(L"command-upgrade_zerg_flyerattacks",					L"image/interface/command/upgrade_zerg_flyerattacks.bmp",				COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//저그 공중유닛 공격
	_loading->loadFrameImage(L"command-upgrade_zerg_flyercarapace",					L"image/interface/command/upgrade_zerg_flyercarapace.bmp",				COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//저그 공중유닛 방어력
									  
	//EVOLUTION						  
	_loading->loadFrameImage(L"command-evolution_zerg_evolve_burrow",				L"image/interface/command/evolution_zerg_evolve_burrow.bmp",			COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//저그 버러우 업글
	_loading->loadFrameImage(L"command-evolution_zerg_metabolick_boost",			L"image/interface/command/evolution_zerg_metabolick_boost.bmp",			COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//저글링 이속업
	_loading->loadFrameImage(L"command-evolution_zerg_adrenal_glands",				L"image/interface/command/evolution_zerg_adrenal_glands.bmp",			COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//저글링 아드레날린
	_loading->loadFrameImage(L"command-evolution_zerg_vectral_sacs",				L"image/interface/command/evolution_zerg_vectral_sacs.bmp",				COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//오버로드 수송업
	_loading->loadFrameImage(L"command-evolution_zerg_antennae",					L"image/interface/command/evolution_zerg_antennae.bmp",					COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//오버로드 시야업
	_loading->loadFrameImage(L"command-evolution_zerg_pneumatized_carapace",		L"image/interface/command/evolution_zerg_pneumatized_carapace.bmp",		COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//오버로드 이속업
	_loading->loadFrameImage(L"command-evolution_zerg_muscular_augments",			L"image/interface/command/evolution_zerg_muscular_augments.bmp",		COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//히드라 이속업
	_loading->loadFrameImage(L"command-evolution_zerg_grooved_spines",				L"image/interface/command/evolution_zerg_grooved_spines.bmp",			COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//히드라 사정거리업
	_loading->loadFrameImage(L"command-evolution_zerg_evolve_lurker_aspect",		L"image/interface/command/evolution_zerg_evolve_lurker_aspect.bmp",		COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//럴커 업글
	_loading->loadFrameImage(L"command-evolution_zerg_evolve_spawn_broodling",		L"image/interface/command/evolution_zerg_evolve_spawn_broodling.bmp",	COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//퀸 브루드링 업글
	_loading->loadFrameImage(L"command-evolution_zerg_evolve_ensnare",				L"image/interface/command/evolution_zerg_evolve_ensnare.bmp",			COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//퀸 인스테어 업글
	_loading->loadFrameImage(L"command-evolution_zerg_gamete_meiosis",				L"image/interface/command/evolution_zerg_gamete_meiosis.bmp",			COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//퀸 마나업
	_loading->loadFrameImage(L"command-evolution_zerg_anabolic_synthesis",			L"image/interface/command/evolution_zerg_anabolic_synthesis.bmp",		COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//울트라 이속업
	_loading->loadFrameImage(L"command-evolution_zerg_chitinous_plating",			L"image/interface/command/evolution_zerg_chitinous_plating.bmp",		COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//울트라 방업(+2)
	_loading->loadFrameImage(L"command-evolution_zerg_evolve_plague",				L"image/interface/command/evolution_zerg_evolve_plague.bmp",			COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//디파일러 플레이그
	_loading->loadFrameImage(L"command-evolution_zerg_evolve_consume",				L"image/interface/command/evolution_zerg_evolve_consume.bmp",			COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//디파일러 컨슘
	_loading->loadFrameImage(L"command-evolution_zerg_metasynaptic_node",			L"image/interface/command/evolution_zerg_metasynaptic_node.bmp",		COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//디파일러 마나업

}

void sceneInit::initImageZergUnits(void)
{
	TCHAR strKey[100];
	TCHAR strFile[100];

	//Body---------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		//larva
		_stprintf(strKey, L"ZU-larva-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/larva/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 288, 36, 8, 1, true, RGB(0, 255, 255));

		//zergegg
		_stprintf(strKey, L"ZU-zergegg-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/zergegg/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 960, 96, 10, 1, true, RGB(0, 255, 255));

		//drone
		_stprintf(strKey, L"ZU-drone-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/drone/Body%d.bmp", i);
		//_loading->loadFrameImage(strKey, strFile, 576, 1008, 8, 14, true, RGB(255, 0, 255));
		_loading->loadFrameImage(strKey, strFile, 1024, 128, 8, 1, true, RGB(0, 255, 255));

		//zergling
		_stprintf(strKey, L"ZU-zergling-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/zergling/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 1024, 128, 8, 1, true, RGB(0, 255, 255));

		//hydralisk
		_stprintf(strKey, L"ZU-hydralisk-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/hydralisk/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 1024, 128, 8, 1, true, RGB(0, 255, 255));


		//lurker
		_stprintf(strKey, L"ZU-lurker-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/lurker/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 1024, 128, 8, 1, true, RGB(0, 255, 255));

		//lurkeregg
		_stprintf(strKey, L"ZU-lurkeregg-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/lurkeregg/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 960, 96, 10, 1, true, RGB(0, 255, 255));

		//ultralisk
		_stprintf(strKey, L"ZU-ultralisk-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/ultralisk/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 1024, 128, 8, 1, true, RGB(0, 255, 255));

		//broodling
		_stprintf(strKey, L"ZU-broodling-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/broodling/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 384, 48, 8, 1, true, RGB(0, 255, 255));

		//defiler
		_stprintf(strKey, L"ZU-defiler-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/defiler/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 640, 80, 8, 1, true, RGB(0, 255, 255));

		//infestedterran
		_stprintf(strKey, L"ZU-infestedterran-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/infestedterran/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 512, 64, 8, 1, true, RGB(0, 255, 255));

		//overlord
		_stprintf(strKey, L"ZU-overlord-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/overlord/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 672, 84, 8, 1, true, RGB(0, 255, 255));


		//mutalisk
		_stprintf(strKey, L"ZU-mutalisk-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/mutalisk/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 1024, 128, 8, 1, true, RGB(0, 255, 255));

		//scourge
		_stprintf(strKey, L"ZU-scourge-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/scourge/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 384, 48, 8, 1, true, RGB(0, 255, 255));

		//queen
		_stprintf(strKey, L"ZU-queen-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/queen/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 1024, 128, 8, 1, true, RGB(0, 255, 255));

		//cocoon

		//guadian
		_stprintf(strKey, L"ZU-guadian-Body%d", i);
		_stprintf(strFile, L"image/zerg/unit/guadian/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 768, 96, 8, 1, true, RGB(0, 255, 255));

		//devourer

	}



	//Stat---------------------------------------------------------------------------------------------------------------------------------
	//larva
	_loading->loadImage(L"ZU-larva-Stat1", L"image/zerg/unit/larva/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-larva-Stat2", L"image/zerg/unit/larva/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-larva-Face",  L"image/zerg/unit/larva/Face.bmp", 50, 55);

	//zergegg
	_loading->loadImage(L"ZU-zergegg-Stat1", L"image/zerg/unit/zergegg/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-zergegg-Stat2", L"image/zerg/unit/zergegg/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-zergegg-Face",  L"image/zerg/unit/zergegg/Face.bmp", 50, 55);


	//drone
	_loading->loadImage(L"ZU-drone-Stat1", L"image/zerg/unit/drone/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-drone-Stat2", L"image/zerg/unit/drone/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-drone-Face",  L"image/zerg/unit/drone/Face.bmp", 50, 55);

	//zergling
	_loading->loadImage(L"ZU-zergling-Stat1", L"image/zerg/unit/zergling/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-zergling-Stat2", L"image/zerg/unit/zergling/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-zergling-Face",  L"image/zerg/unit/zergling/Face.bmp", 50, 55);

	//hydralisk
	_loading->loadImage(L"ZU-hydralisk-Stat1", L"image/zerg/unit/hydralisk/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-hydralisk-Stat2", L"image/zerg/unit/hydralisk/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-hydralisk-Face",  L"image/zerg/unit/hydralisk/Face.bmp", 50, 55);


	//lurker
	_loading->loadImage(L"ZU-lurker-Stat1", L"image/zerg/unit/lurker/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-lurker-Stat2", L"image/zerg/unit/lurker/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-lurker-Face",  L"image/zerg/unit/lurker/Face.bmp", 50, 55);

	//lurkeregg
	_loading->loadImage(L"ZU-lurkeregg-Stat1", L"image/zerg/unit/lurkeregg/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-lurkeregg-Stat2", L"image/zerg/unit/lurkeregg/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-lurkeregg-Face",  L"image/zerg/unit/lurkeregg/Face.bmp", 50, 55);

	//ultralisk
	_loading->loadImage(L"ZU-ultralisk-Stat1", L"image/zerg/unit/ultralisk/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-ultralisk-Stat2", L"image/zerg/unit/ultralisk/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-ultralisk-Face",  L"image/zerg/unit/ultralisk/Face.bmp", 50, 55);

	//broodling
	_loading->loadImage(L"ZU-broodling-Stat1", L"image/zerg/unit/broodling/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-broodling-Stat2", L"image/zerg/unit/broodling/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-broodling-Face",  L"image/zerg/unit/broodling/Face.bmp", 50, 55);

	//defiler
	_loading->loadImage(L"ZU-defiler-Stat1", L"image/zerg/unit/defiler/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-defiler-Stat2", L"image/zerg/unit/defiler/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-defiler-Face",  L"image/zerg/unit/defiler/Face.bmp", 50, 55);

	//infestedterran

	//overlord
	_loading->loadImage(L"ZU-overlord-Stat1", L"image/zerg/unit/overlord/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-overlord-Stat2", L"image/zerg/unit/overlord/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-overlord-Face",  L"image/zerg/unit/overlord/Face.bmp", 50, 55);

	//mutalisk
	_loading->loadImage(L"ZU-mutalisk-Stat1", L"image/zerg/unit/mutalisk/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-mutalisk-Stat2", L"image/zerg/unit/mutalisk/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-mutalisk-Face",  L"image/zerg/unit/mutalisk/Face.bmp", 50, 55);

	//scourge
	_loading->loadImage(L"ZU-scourge-Stat1", L"image/zerg/unit/scourge/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-scourge-Stat2", L"image/zerg/unit/scourge/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-scourge-Face",  L"image/zerg/unit/scourge/Face.bmp", 50, 55);

	//queen
	_loading->loadImage(L"ZU-queen-Stat1", L"image/zerg/unit/queen/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-queen-Stat2", L"image/zerg/unit/queen/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-queen-Face",  L"image/zerg/unit/queen/Face.bmp", 50, 55);

	//cocoon
	_loading->loadImage(L"ZU-cocoon-Stat1", L"image/zerg/unit/cocoon/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-cocoon-Stat2", L"image/zerg/unit/cocoon/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-cocoon-Face",  L"image/zerg/unit/cocoon/Face.bmp", 50, 55);

	//guadian
	_loading->loadImage(L"ZU-guadian-Stat1", L"image/zerg/unit/guadian/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-guadian-Stat2", L"image/zerg/unit/guadian/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-guadian-Face",  L"image/zerg/unit/guadian/Face.bmp", 50, 55);

	//devourer
	_loading->loadImage(L"ZU-devourer-Stat1", L"image/zerg/unit/devourer/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));
	_loading->loadImage(L"ZU-devourer-Stat2", L"image/zerg/unit/devourer/Stat2.bmp", 33, 34);
	_loading->loadImage(L"ZU-devourer-Face",  L"image/zerg/unit/devourer/Face.bmp", 50, 55);


}

void sceneInit::initImageZergBuildings(void)
{
	_loading->loadFrameImage(L"ZB-MutatingBody1", L"image/zerg/build/morphing/zbuild1.bmp", 1760, 192, 11, 1, true, RGB(0, 255, 255));
	_loading->loadFrameImage(L"ZB-MutatingBody2", L"image/zerg/build/morphing/zbuild2.bmp", 1760, 192, 11, 1, true, RGB(0, 255, 255));
	_loading->loadFrameImage(L"ZB-MutatingBody3", L"image/zerg/build/morphing/zbuild3.bmp", 1760, 192, 11, 1, true, RGB(0, 255, 255));

	_loading->loadImage(L"ZB-Face", L"image/zerg/build/Face.bmp", 50, 55);

	TCHAR strKey[100];
	TCHAR strFile[100];

	//Body---------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		//hatchery
		_stprintf(strKey, L"ZB-hatchery-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/hatchery/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 192, 960, 1, 6, true, RGB(0, 255, 255)); //6, 5 타일이미지이고 실제 크기는 4,3 임

		//lair
		_stprintf(strKey, L"ZB-lair-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/lair/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 960, 160, 5, 1, true, RGB(0, 255, 255));

		//hive
		_stprintf(strKey, L"ZB-hive-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/hive/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 960, 224, 5, 1, true, RGB(0, 255, 255));

		//creepcolony
		_stprintf(strKey, L"ZB-creepcolony-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/creepcolony/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 512, 64, 4, 1, true, RGB(0, 255, 255));

		//sunkencolony

		//sporecolony
		_stprintf(strKey, L"ZB-sporecolony-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/sporecolony/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 512, 128, 4, 1, true, RGB(0, 255, 255));

		//extractor
		_stprintf(strKey, L"ZB-extractor-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/extractor/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 128, 768, 1, 4, true, RGB(0, 255, 255));

		//spawningpool
		_stprintf(strKey, L"ZB-spawningpool-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/spawningpool/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 384, 128, 4, 1, true, RGB(0, 255, 255));

		//evolutionchamber
		_stprintf(strKey, L"ZB-evolutionchamber-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/evolutionchamber/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 288, 128, 3, 1, true, RGB(0, 255, 255));

		//hydraliskden
		_stprintf(strKey, L"ZB-hydraliskden-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/hydraliskden/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 480, 128, 3, 1, true, RGB(0, 255, 255));

		//spire
		_stprintf(strKey, L"ZB-spire-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/spire/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 512, 128, 4, 1, true, RGB(0, 255, 255));

		//greaterspire
		_stprintf(strKey, L"ZB-greaterspire-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/greaterspire/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 128, 768, 1, 4, true, RGB(0, 255, 255));

		//queensnest
		_stprintf(strKey, L"ZB-queensnest-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/queensnest/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 384, 128, 4, 1, true, RGB(0, 255, 255));

		//nyduscanal
		_stprintf(strKey, L"ZB-nyduscanal-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/nyduscanal/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 640, 128, 5, 1, true, RGB(0, 255, 255));

		//ultraliskcavern
		_stprintf(strKey, L"ZB-ultraliskcavern-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/ultraliskcavern/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 480, 128, 3, 1, true, RGB(0, 255, 255));

		//defilermound
		_stprintf(strKey, L"ZB-defilermound-Body%d", i);
		_stprintf(strFile, L"image/zerg/build/defilermound/Body%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 512, 128, 4, 1, true, RGB(0, 255, 255));

		//infestedcommandcenter

	}


	//hatchery
	_loading->loadImage(L"ZB-hatchery-Stat1", L"image/zerg/build/hatchery/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));


	//lair
	_loading->loadImage(L"ZB-lair-Stat1", L"image/zerg/build/lair/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//hive
	_loading->loadImage(L"ZB-hive-Stat1", L"image/zerg/build/hive/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//creepcolony
	_loading->loadImage(L"ZB-creepcolony-Stat1", L"image/zerg/build/creepcolony/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//sunkencolony
	_loading->loadImage(L"ZB-sunkencolony-Stat1", L"image/zerg/build/sunkencolony/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//sporecolony
	_loading->loadImage(L"ZB-sporecolony-Stat1", L"image/zerg/build/sporecolony/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//extractor
	_loading->loadImage(L"ZB-extractor-Stat1", L"image/zerg/build/extractor/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//spawningpool
	_loading->loadImage(L"ZB-spawningpool-Stat1", L"image/zerg/build/spawningpool/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//evolutionchamber
	_loading->loadImage(L"ZB-evolutionchamber-Stat1", L"image/zerg/build/evolutionchamber/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//hydraliskden
	_loading->loadImage(L"ZB-hydraliskden-Stat1", L"image/zerg/build/hydraliskden/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//spire
	_loading->loadImage(L"ZB-spire-Stat1", L"image/zerg/build/spire/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//greaterspire
	_loading->loadImage(L"ZB-greaterspire-Stat1", L"image/zerg/build/greaterspire/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//queensnest
	_loading->loadImage(L"ZB-queensnest-Stat1", L"image/zerg/build/queensnest/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//nyduscanal
	_loading->loadImage(L"ZB-nyduscanal-Stat1", L"image/zerg/build/nyduscanal/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//ultraliskcavern
	_loading->loadImage(L"ZB-ultraliskcavern-Stat1", L"image/zerg/build/ultraliskcavern/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//defilermound
	_loading->loadImage(L"ZB-defilermound-Stat1", L"image/zerg/build/defilermound/Stat1.bmp", 89, 96, true, RGB(255, 0, 255));

	//infestedcommandcenter

}