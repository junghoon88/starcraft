#pragma once
#include "stdafx.h"


//한 타일의 규격
#define TILESIZE	32

//타일 갯수
#define TILEX		128
#define TILEY		128

//게임맵, 맵에디터에서 보여줄 타일 개수
#define TILEVIEWX	30
#define TILEVIEWY	30

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
	OBJECTSELECT_ENEMY,
	OBJECTSELECT_AILY,
	OBJECTSELECT_PLAYER,

	OBJECTSELECT_MAX
};

//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	TCHAR obj[128];
	RECT rc;

	INT terrainNum;		//샘플 터레인 인덱스
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
