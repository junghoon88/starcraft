#pragma once

#define CAMERA_SPEED		10

#define MAP_WIDTH			(TILESIZE*TILEX)
#define MAP_HEIGHT			(TILESIZE*TILEY)

#define COMMAND_MAX		9

#define TEXTCOLOR_UNITHP	RGB(17, 248, 25)
#define TEXTCOLOR_UNITMP	RGB(255, 255, 255)


#define COMMAND_WIDTH		32
#define COMMAND_HEIGHT		32


#define OBJECTSIZE_MAX_X	4
#define OBJECTSIZE_MAX_Y	4

#define OBJ_MINERAL_WIDTH			2
#define OBJ_MINERAL_HEIGHT			1
#define OBJ_GAS_WIDTH				4
#define OBJ_GAS_HEIGHT				2
#define OBJ_LOCATION_PLAYER_WIDTH	4
#define OBJ_LOCATION_PLAYER_HEIGHT	3
#define OBJ_ERASER_WIDTH			1
#define OBJ_ERASER_HEIGHT			1


#define BUILDSPEEDMULTIPLY		25.0f

#define UNIT_BODY_FPS_TIME		(1/15.0f)

//command
enum COMMAND
{
	//COMMON
	COMMAND_NONE,			
	COMMAND_ESC,
	COMMAND_MOVE,			
	COMMAND_STOP,			
	COMMAND_ATTACK,			
	COMMAND_PATROL,			
	COMMAND_HOLD,			
	COMMAND_GATHER,			
	COMMAND_RETURNCARGO,	
	COMMAND_BUILD1,			
	COMMAND_BUILD2,	
	COMMAND_SELECT_LARVA,
	COMMAND_SETRALLYPOINT,

	//ZERG
	COMMAND_BURROW,			
	COMMAND_UNBURROW,		
	COMMAND_INFEST,			
	COMMAND_PARASITE,
	COMMAND_BROODRING,		
	COMMAND_ENSNARE,		
	COMMAND_CONSUME,		
	COMMAND_DARKSWARM,		
	COMMAND_PLAGUE,			

	//BUILD1
	COMMAND_BUILD_HATCHERY,
	COMMAND_BUILD_LAIR,
	COMMAND_BUILD_HIVE,
	COMMAND_BUILD_CREEPCOLONY,
	COMMAND_BUILD_SUNKENCOLONY,
	COMMAND_BUILD_SPORECOLONY,
	COMMAND_BUILD_EXTRACTOR,
	COMMAND_BUILD_SPAWNINGPOOL,
	COMMAND_BUILD_EVOLUTIONCHAMBER,
	COMMAND_BUILD_HYDRALISKDEN,
	//BUILD2
	COMMAND_BUILD_SPIRE,
	COMMAND_BUILD_GREATERSPIRE,
	COMMAND_BUILD_QUEENSNEST,
	COMMAND_BUILD_NYDUSCANAL,
	COMMAND_BUILD_ULTRALISKCAVERN,
	COMMAND_BUILD_DEFILERMOUND,

	//UNIT
	COMMAND_UNIT_DRONE,
	COMMAND_UNIT_ZERGLING,
	COMMAND_UNIT_OVERLORD,
	COMMAND_UNIT_HYDRALISK,
	COMMAND_UNIT_MUTALISK,
	COMMAND_UNIT_SCOURGE,
	COMMAND_UNIT_QUEEN,
	COMMAND_UNIT_ULTRALISK,
	COMMAND_UNIT_DEFILER,
	//UNIT2
	COMMAND_UNIT_LURKER,
	COMMAND_UNIT_GUADIAN,
	COMMAND_UNIT_DEVOURER,
	COMMAND_UNIT_INFESTEDTERRAN,

	//UPGRADE
	COMMAND_UPGRADE_ZERG_MELEEATTACKS,		//저그 지상유닛 근접 공격
	COMMAND_UPGRADE_ZERG_MISSILEATTACKS,	//저그 지상유닛 원거리 공격
	COMMAND_UPGRADE_ZERG_CARAPACE,			//저그 지상유닛 방어력
	COMMAND_UPGRADE_ZERG_FLYERATTACKS,		//저그 공중유닛 공격
	COMMAND_UPGRADE_ZERG_FLYERCARAPACE,		//저그 공중유닛 방어력

	//EVOLUTION
	COMMAND_EVOLUTION_ZERG_EVOLVE_BURROW,			//저그 버러우 업글
	COMMAND_EVOLUTION_ZERG_METABOLICK_BOOST,		//저글링 이속업
	COMMAND_EVOLUTION_ZERG_ADRENAL_GLANDS,			//저글링 아드레날린
	COMMAND_EVOLUTION_ZERG_VECTRAL_SACS,			//오버로드 수송업
	COMMAND_EVOLUTION_ZERG_ANTENNAE,				//오버로드 시야업
	COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE,	//오버로드 이속업
	COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS,		//히드라 이속업
	COMMAND_EVOLUTION_ZERG_GROOVED_SPINES,			//히드라 사정거리업
	COMMAND_EVOLUTION_ZERG_EVOLVE_LURKER_ASPECT,	//럴커 업글
	COMMAND_EVOLUTION_ZERG_EVOLVE_SPAWN_BROODLING,	//퀸 브루드링 업글
	COMMAND_EVOLUTION_ZERG_EVOLVE_ENSNARE,			//퀸 인스테어 업글
	COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS,			//퀸 마나업
	COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS,		//울트라 이송업
	COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING,		//울트라 방업(+2)
	COMMAND_EVOLUTION_ZERG_EVOLVE_PLAGUE,			//디파일러 플레이그
	COMMAND_EVOLUTION_ZERG_EVOLVE_CONSUME,			//디파일러 컨슘
	COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE,		//디파일러 마나업

	COMMAND_NUM
};

enum FONTVERSION
{
	FONTVERSION_STARCRAFT,

	FONTVERSION_MAX
};

enum BRUSHVERSION
{
	BRUSHVERSION_WHITE,
	BRUSHVERSION_GRAY,
	BRUSHVERSION_BLACK,

	BRUSHVERSION_MAX
};

enum PENVERSION
{
	PENVERSION_MOUSEDRAG,
	PENVERSION_UNITCLICK,
	

	PENVERSION_BLUE1,
	PENVERSION_BLUE2,
	PENVERSION_MINIMAP,

	PENVERSION_MAX
};


enum DIRECTION
{
	DIRECTION_NONE = 0,
	DIRECTION_RG,
	DIRECTION_RU,
	DIRECTION_UP,
	DIRECTION_LU,
	DIRECTION_LF,
	DIRECTION_LD,
	DIRECTION_DN,
	DIRECTION_RD,
};

enum PLAYER
{
	PLAYER_NONE = -1,
	PLAYER1,
	//PLAYER2,

	PLAYER_NUM
};

enum RACES
{
	RACES_TERRAN,
	RACES_PROTOSS,
	RACES_ZERG,

	RACES_NUM
};

enum TEAM
{
	TEAM_NONE = -1,
	TEAM_NEUTRAL,
	TEAM_MYTEAM,
	TEAM_FRIEND,
	TEAM_ENEMY,

};

enum UNITSIZE
{
	UNITSIZE_SMALL,
	UNITSIZE_MEDIUM,
	UNITSIZE_LARGE
};

enum DAMAGETYPE
{
	DAMAGETYPE_NORMAL,		//일반공격
	DAMAGETYPE_CONCUSSIVE,	//진동형
	DAMAGETYPE_EXPLOSIVE	//폭발형
};

enum UNITNUM_ZERG
{
	//GROUND
	UNITNUM_ZERG_NONE = -1,
	UNITNUM_ZERG_LARVA,
	UNITNUM_ZERG_ZERGEGG,
	UNITNUM_ZERG_DRONE,
	UNITNUM_ZERG_ZERGLING,
	UNITNUM_ZERG_HYDRALISK,
	UNITNUM_ZERG_LURKER,
	UNITNUM_ZERG_LURKEREGG,
	UNITNUM_ZERG_ULTRALISK,
	UNITNUM_ZERG_BROODLING,
	UNITNUM_ZERG_DEFILER,
	UNITNUM_ZERG_INFESTEDTERRAN,

	//AIR
	UNITNUM_ZERG_OVERLORD,
	UNITNUM_ZERG_MUTALISK,
	UNITNUM_ZERG_SCOURGE,
	UNITNUM_ZERG_QUEEN,
	UNITNUM_ZERG_COCOON,
	UNITNUM_ZERG_GUADIAN,
	UNITNUM_ZERG_DEVOURER,

	UNITNUM_ZERG_MAX
};



enum BUILDINGNUM_ZERG
{
	BUILDINGNUM_ZERG_NONE = -1,

	//BUILD1
	BUILDINGNUM_ZERG_HATCHERY,
	BUILDINGNUM_ZERG_LAIR,
	BUILDINGNUM_ZERG_HIVE,

	BUILDINGNUM_ZERG_CREEPCOLONY,
	BUILDINGNUM_ZERG_SUNKENCOLONY,
	BUILDINGNUM_ZERG_SPORECOLONY,

	BUILDINGNUM_ZERG_EXTRACTOR,

	BUILDINGNUM_ZERG_SPAWNINGPOOL,

	BUILDINGNUM_ZERG_EVOLUTIONCHAMBER,

	BUILDINGNUM_ZERG_HYDRALISKDEN,

	//BUILD2
	BUILDINGNUM_ZERG_SPIRE,
	BUILDINGNUM_ZERG_GREATERSPIRE,

	BUILDINGNUM_ZERG_QUEENSNEST,

	BUILDINGNUM_ZERG_NYDUSCANAL,

	BUILDINGNUM_ZERG_ULTRALISKCAVERN,

	BUILDINGNUM_ZERG_DEFILERMOUND,

	//SPECIAL
	BUILDINGNUM_ZERG_INFESTEDCOMMANDCENTER,

	BUILDINGNUM_ZERG_MAX
};

enum BUILDINGNUM_TERRAN
{
	BUILDINGNUM_TERRAN_NONE = -1,

	BUILDINGNUM_TERRAN_MAX
};

enum BUILDINGNUM_PROTOSS
{
	BUILDINGNUM_PROTOSS_NONE = -1,

	BUILDINGNUM_PROTOSS_MAX
};

enum UPGRADE_ZERG
{
	UPGRADE_ZERG_MELEEATTACKS,		//저그 지상유닛 근접 공격
	UPGRADE_ZERG_MISSILEATTACKS,	//저그 지상유닛 원거리 공격
	UPGRADE_ZERG_CARAPACE,			//저그 지상유닛 방어력
	UPGRADE_ZERG_FLYERATTACKS,		//저그 공중유닛 공격
	UPGRADE_ZERG_FLYERCARAPACE,		//저그 공중유닛 방어력

	UPGRADE_ZERG_MAX
};

enum EVOLUTION_ZERG
{
	EVOLUTION_ZERG_EVOLVE_BURROW,			//저그 버러우 업글

	EVOLUTION_ZERG_METABOLICK_BOOST,		//저글링 이속업
	EVOLUTION_ZERG_ADRENAL_GLANDS,			//저글링 아드레날린

	EVOLUTION_ZERG_VECTRAL_SACS,			//오버로드 수송업
	EVOLUTION_ZERG_ANTENNAE,				//오버로드 시야업
	EVOLUTION_ZERG_PNEUMATIZED_CARAPACE,	//오버로드 이속업

	EVOLUTION_ZERG_MUSCULAR_AUGMENTS,		//히드라 이속업
	EVOLUTION_ZERG_GROOVED_SPINES,			//히드라 사정거리업
	EVOLUTION_ZERG_EVOLVE_LURKER_ASPECT,	//럴커 업글

	EVOLUTION_ZERG_EVOLVE_SPAWN_BROODLING,	//퀸 브루드링 업글
	EVOLUTION_ZERG_EVOLVE_ENSNARE,			//퀸 인스테어 업글
	EVOLUTION_ZERG_GAMETE_MEIOSIS,			//퀸 마나업

	EVOLUTION_ZERG_ANABOLIC_SYNTHESIS,		//울트라 이송업
	EVOLUTION_ZERG_CHITINOUS_PLATING,		//울트라 방업(+2)

	EVOLUTION_ZERG_EVOLVE_PLAGUE,			//디파일러 플레이그
	EVOLUTION_ZERG_EVOLVE_CONSUME,			//디파일러 컨슘
	EVOLUTION_ZERG_METASYNAPTIC_NODE,		//디파일러 마나업
	
	
	EVOLUTION_ZERG_MAX
};

enum ATTACKTYPE
{
	ATTACKTYPE_ZERG_NONE,
	ATTACKTYPE_ZERG_WORKER,
	ATTACKTYPE_ZERG_MELEE,
	ATTACKTYPE_ZERG_MISSILE,
	ATTACKTYPE_ZERG_FLYING
};

enum UNITNUM_TERRAN
{
	//GROUND
	UNITNUM_TERRAN_NONE = -1,
	UNITNUM_TERRAN_SCV,
	UNITNUM_TERRAN_MARINE,
	UNITNUM_TERRAN_FIREBAT,
	UNITNUM_TERRAN_MEDIC,
	UNITNUM_TERRAN_GHOST,
	UNITNUM_TERRAN_VULTURE,
	UNITNUM_TERRAN_SPIDERMINE,
	UNITNUM_TERRAN_SIEGETANK_TANKMODE,
	UNITNUM_TERRAN_SIEGETANK_SIEGEMODE,
	UNITNUM_TERRAN_GOLIATH,

	//AIR
	UNITNUM_TERRAN_WRAITH,
	UNITNUM_TERRAN_DROPSHIP,
	UNITNUM_TERRAN_SCIENCEVESSEL,
	UNITNUM_TERRAN_VALKYRIE,
	UNITNUM_TERRAN_BATTLECRUISER,
};

enum UNITNUM_PROTOSS
{
	//GROUND
	UNITNUM_PROTOSS_NONE = -1,
	UNITNUM_PROTOSS_PROBE,
	UNITNUM_PROTOSS_ZEALOT,
	UNITNUM_PROTOSS_DRAGOON,
	UNITNUM_PROTOSS_HIGHTEMPLAR,
	UNITNUM_PROTOSS_ARCHON,
	UNITNUM_PROTOSS_DARKTEMPLAR,
	UNITNUM_PROTOSS_DARKARCHON,
	UNITNUM_PROTOSS_REAVER,
	UNITNUM_PROTOSS_SCARAB,


	//AIR
	UNITNUM_PROTOSS_SHUTTLE,
	UNITNUM_PROTOSS_OBSERVER,
	UNITNUM_PROTOSS_SCOUT,
	UNITNUM_PROTOSS_CORSAIR,
	UNITNUM_PROTOSS_ARBITER,
	UNITNUM_PROTOSS_CARRIER,
	UNITNUM_PROTOSS_INTERCEPTOR,
};

