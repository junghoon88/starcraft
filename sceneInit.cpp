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
}

void sceneInit::initSound(void)
{

}

void sceneInit::initImageNeutralResource(void)
{
	_loading->loadFrameImage(L"NeutralResource-Mineral0", L"image/neutral/min00.bmp", 64, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"NeutralResource-Mineral1", L"image/neutral/min01.bmp", 64, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"NeutralResource-Mineral2", L"image/neutral/min02.bmp", 64, 384, 1, 4, true, RGB(255, 0, 255));
	_loading->loadImage(L"NeutralResource-Gas", L"image/neutral/gas.bmp", MAPTOOL_TILESIZE * 4, MAPTOOL_TILESIZE * 2, true, RGB(255, 0, 255));
}

void sceneInit::initImageMaptoolTiles(void)
{
	TCHAR strKey[128] = L"";
	TCHAR strFile[128] = L"";


	//terrain-Dirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Dirt-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Dirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-HighDirt
	_loading->loadFrameImage(L"maptool-terrain-HighDirt", L"image/maptool/tiles/terrain-HighDirt/IDLE3x2.bmp", MAPTOOL_TILESIZE*3, MAPTOOL_TILESIZE*2, 3, 2);

	_loading->loadFrameImage(L"maptool-terrain-HighDirt-LD", L"image/maptool/tiles/terrain-HighDirt/LD2x3.bmp", MAPTOOL_TILESIZE * 2, MAPTOOL_TILESIZE * 3, 2, 3);
	_loading->loadFrameImage(L"maptool-terrain-HighDirt-LF", L"image/maptool/tiles/terrain-HighDirt/LF2x3.bmp", MAPTOOL_TILESIZE * 2, MAPTOOL_TILESIZE * 3, 2, 3);
	_loading->loadFrameImage(L"maptool-terrain-HighDirt-LU", L"image/maptool/tiles/terrain-HighDirt/LU2x2.bmp", MAPTOOL_TILESIZE * 2, MAPTOOL_TILESIZE * 2, 2, 2);

	_loading->loadFrameImage(L"maptool-terrain-HighDirt-RD", L"image/maptool/tiles/terrain-HighDirt/RD2x3.bmp", MAPTOOL_TILESIZE * 2, MAPTOOL_TILESIZE * 3, 2, 3);
	_loading->loadFrameImage(L"maptool-terrain-HighDirt-RG", L"image/maptool/tiles/terrain-HighDirt/RG2x3.bmp", MAPTOOL_TILESIZE * 2, MAPTOOL_TILESIZE * 3, 2, 3);
	_loading->loadFrameImage(L"maptool-terrain-HighDirt-RU", L"image/maptool/tiles/terrain-HighDirt/RU2x2.bmp", MAPTOOL_TILESIZE * 2, MAPTOOL_TILESIZE * 2, 2, 2);

	//terrain-Water
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Water-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Water/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//icon
	_loading->loadImage(L"maptool-icon-Mineral",	L"image/maptool/iconMineral.bmp",		MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_loading->loadImage(L"maptool-icon-Gas",		L"image/maptool/iconGas.bmp",			MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_loading->loadImage(L"maptool-icon-LocationP1", L"image/maptool/iconLocationP1.bmp",	MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, true, RGB(255, 0, 255));
	_loading->loadImage(L"maptool-icon-LocationP2", L"image/maptool/iconLocationP2.bmp",	MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, true, RGB(255, 0, 255));



#if 0
	//terrain-Asphlat
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Asphlat-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Asphlat/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}


	//terrain-Grass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Grass-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Grass/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-HighDirt-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-HighGrass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-HighGrass-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-Mud
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Mud-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Mud/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-RockyGround
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-RockyGround-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-RockyGround/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-Structure
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Structure-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Structure/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}
#endif
}

void sceneInit::initImageGamemapTiles(void)
{
	TCHAR strKey[128] = L"";
	TCHAR strFile[128] = L"";

	_loading->loadImage(L"gamemap-fog", L"image/gamemap/fog.bmp", GAMEMAP_TILESIZE, GAMEMAP_TILESIZE, false, RGB(0, 0, 0), true);

	//terrain-Asphlat
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Asphlat-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Asphlat/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Dirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Dirt-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Dirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Grass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Grass-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Grass/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-HighDirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-HighDirt-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-HighGrass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-HighGrass-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Mud
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Mud-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Mud/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-RockyGround
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-RockyGround-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-RockyGround/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Structure
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Structure-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Structure/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Water
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Water-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Water/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}
}

void sceneInit::initImageInterface(void)
{
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
	_loading->loadFrameImage(L"command-evolution_zerg_anabolic_synthesis",			L"image/interface/command/evolution_zerg_anabolic_synthesis.bmp",		COMMAND_WIDTH * 3, COMMAND_HEIGHT, 3, 1, true, RGB(0, 0, 0));	//울트라 이송업
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
		//drone
		_stprintf(strKey, L"ZU-droneBody%d", i);
		_stprintf(strFile, L"image/zerg/unit/drone/droneBody%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 576, 1008, 8, 14, true, RGB(255, 0, 255));


	}

	//Stat---------------------------------------------------------------------------------------------------------------------------------
	//drone
	_loading->loadFrameImage(L"ZU-droneStat1", L"image/zerg/unit/drone/droneStat1.bmp", 59, 51, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"ZU-droneStat2", L"image/zerg/unit/drone/droneStat2.bmp", 33, 34, 1, 1);

}

