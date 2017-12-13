#pragma once
#include "stdafx.h"

//타일 갯수
#define TILEX		128
#define TILEY		128

//맵툴-----------------------------------------------------------------
//한 타일의 규격
#define MAPTOOL_TILESIZE	32

//게임맵, 맵툴에서 보여줄 타일 개수
#define MAPTOOL_TILEVIEWX	20
#define MAPTOOL_TILEVIEWY	15

//맵툴 ISOTILE
#define ISOTILE_WIDTH		(MAPTOOL_TILESIZE*4)
#define ISOTILE_HEIGHT		(MAPTOOL_TILESIZE*2)

#define ISOTILE_HALF_WIDTH	(MAPTOOL_TILESIZE*2)
#define ISOTILE_HALF_HEIGHT	(MAPTOOL_TILESIZE)

#define ISOTILEX			(MAPTOOL_TILEVIEWX/2)
#define ISOTILEY			(MAPTOOL_TILEVIEWY)
//~맵툴-----------------------------------------------------------------

//게임맵----------------------------------------------------------------
#define GAMEMAP_TILESIZE		32

#define GAMEMAP_TILEVIEWX		20
#define GAMEMAP_TILEVIEWY		12 //30



//~게임맵---------------------------------------------------------------


//비트필드 타일 속성
#define ATTR_INCASTLE	0x00000001	//

//맵타일에 들어갈 터레인속성
enum TERRAIN
{
	TERRAIN_DIRT,			//
	TERRAIN_MUD,			//
	TERRAIN_DIRTWALL,		//
	TERRAIN_WATER,			//
	TERRAIN_GRASS,			//
	TERRAIN_GRASSWALL,		//
	TERRAIN_STRUCTURE,		//
	TERRAIN_STRUCTUREWALL,	//
	TERRAIN_ASPHALT,		//
	TERRAIN_ROCKYGROUND,	//

	TERRAIN_MAX
};

//맵에디터에서 선택할 터레인 종류
enum TERRAINSET
{
	TERRAINSET_DIRT,		//
	TERRAINSET_MUD,			//
	TERRAINSET_HIGHDIRT,	//
	TERRAINSET_WATER,		//
	TERRAINSET_GRASS,		//
	TERRAINSET_HIGHGRASS,	//
	TERRAINSET_STRUCTURE,	//
	TERRAINSET_ASPHALT,		//
	TERRAINSET_ROCKYGROUND,	//

	TERRAINSET_MAX
};

//오브젝트 선택
enum OBJECTSELECT
{
	OBJECTSELECT_NONE = -1,
	
	OBJECTSELECT_MAX
};

enum FOGLEVEL
{
	FOGLEVEL_BLACK,		//검은화면
	FOGLEVEL_GRAY,		//이전에 확보했던 시야
	FOGLEVEL_VIEW,		//현재 시야
	FOGLEVEL_DETECT,	//디텍트 가능 시야

};

//타일 구조체
struct tagTile
{
	TERRAIN terrain;	//터레인
	INT terrainNum;		//터레인 인덱스

	DWORD obj;			//
	RECT rc;			//

	BOOL isClick;		//오브젝트 선택
};

struct tagSampleTile
{
	RECT rcTile;
	image* img;
	TCHAR strImgKey[100];
};

struct tagSampleObject
{
	RECT rcTile;
	image* img;
	TCHAR strImgKey[100];
};

struct tagCurrentTile
{
	int x;
	int y;
};

struct tagisoTile
{
	POINT pt;
	RECT rc;

	bool clicked;
};


struct tagFog
{
	RECT		rcFog;
	FOGLEVEL	level;
	BYTE		alpha;
};