#pragma once
#include "stdafx.h"

//타일 갯수
#define TILEX		128
#define TILEY		128

//맵툴-----------------------------------------------------------------
//한 타일의 규격
#define MAPTOOL_TILESIZE	32

//게임맵, 맵툴에서 보여줄 타일 개수
#define MAPTOOL_TILEVIEWX	15 //20 이 최대크기
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
#define ATTR_UNMOVE		0x00000001	//


#define HIGHTDIRT_LF  0x0001
#define HIGHTDIRT_RG  0x0002
#define HIGHTDIRT_UP  0x0004
#define HIGHTDIRT_DN  0x0008


//맵타일에 들어갈 터레인속성
enum TERRAIN
{
	TERRAIN_DIRT			= 0x1000,			

	TERRAIN_HIGHTDIRT		= 0x2000,
	TERRAIN_HIGHTDIRT_LF	= TERRAIN_HIGHTDIRT + HIGHTDIRT_LF,
	TERRAIN_HIGHTDIRT_LU	= TERRAIN_HIGHTDIRT + HIGHTDIRT_LF + HIGHTDIRT_UP,
	TERRAIN_HIGHTDIRT_LD	= TERRAIN_HIGHTDIRT + HIGHTDIRT_LF + HIGHTDIRT_DN,
	TERRAIN_HIGHTDIRT_RG	= TERRAIN_HIGHTDIRT + HIGHTDIRT_RG,
	TERRAIN_HIGHTDIRT_RU	= TERRAIN_HIGHTDIRT + HIGHTDIRT_RG + HIGHTDIRT_UP,
	TERRAIN_HIGHTDIRT_RD	= TERRAIN_HIGHTDIRT + HIGHTDIRT_RG + HIGHTDIRT_DN,


	//TERRAIN_DIRTWALL,		
	TERRAIN_WATER			= 0x4000,

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
	DWORD	terrain;	//터레인
	POINT	terrainNum;		//터레인 인덱스

	DWORD	obj;			//
	UINT	nrAmount;//NeutralResource 자원양

	DWORD	attribute;
	
	RECT	rc;			//
};

struct tagSampleTile
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