#pragma once
#include "stdafx.h"

//타일 갯수
#define TILEX		128
#define TILEY		128

//한 타일의 규격
#define TILESIZE	32

//맵툴-----------------------------------------------------------------
//맵툴에서 보여줄 타일 개수
#define MAPTOOL_TILEVIEWX	15 //20 이 최대크기
#define MAPTOOL_TILEVIEWY	15

//맵툴 ISOTILE
#define ISOTILE_WIDTH		(TILESIZE*4)
#define ISOTILE_HEIGHT		(TILESIZE*2)

#define ISOTILE_HALF_WIDTH	(TILESIZE*2)
#define ISOTILE_HALF_HEIGHT	(TILESIZE)
//~맵툴-----------------------------------------------------------------

//게임맵----------------------------------------------------------------
//게임맵에서 보여줄 타일 개수
#define GAMEMAP_TILEVIEWX		20
#define GAMEMAP_TILEVIEWY		12 //30



//~게임맵---------------------------------------------------------------


//비트필드 타일 속성
#define ATTR_UNMOVE		0x00000001	//
#define ATTR_UNBUILD	0x00000002	//
#define ATTR_CREEP		0x00000004



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

enum OBJECT
{
	OBJECT_NONE, 

	//자원(미네랄, 가스)
	OBJECT_MINERAL1_START,	//미네랄의 (0,0)위치
	OBJECT_MINERAL1_BODY,	//미네랄이 차지하는 (0,0) 제외 위치
	OBJECT_MINERAL2_START,	//미네랄의 이미지는 총 3가지(랜덤배치)
	OBJECT_MINERAL2_BODY,	//
	OBJECT_MINERAL3_START,	//
	OBJECT_MINERAL3_BODY,	//
	OBJECT_GAS_START,		//가스의 (0,0)위치
	OBJECT_GAS_BODY,		//가스가 차지하는 (0,0) 제외 위치

	//플레이어 시작위치
	OBJECT_LOCATION_P1_START,		//플레이어 시작위치 (0,0)위치
	OBJECT_LOCATION_P1_BODY,		//플레이어 시작위치 (0,0)제외 위치
	OBJECT_LOCATION_P2_START,		//
	OBJECT_LOCATION_P2_BODY,		//
	
	//여기까지는 맵툴에서만 사용

	//여기부터는 게임맵에서 추가될 수 있음

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
	DWORD	terrain;		//터레인
	POINT	terrainNum;		//터레인 인덱스

	DWORD	obj;			//
	UINT	nrAmount;		//NeutralResource 자원양

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