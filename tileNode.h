#pragma once
#include "stdafx.h"

//Ÿ�� ����
#define TILEX		128
#define TILEY		128

//����-----------------------------------------------------------------
//�� Ÿ���� �԰�
#define MAPTOOL_TILESIZE	32

//���Ӹ�, �������� ������ Ÿ�� ����
#define MAPTOOL_TILEVIEWX	15 //20 �� �ִ�ũ��
#define MAPTOOL_TILEVIEWY	15

//���� ISOTILE
#define ISOTILE_WIDTH		(MAPTOOL_TILESIZE*4)
#define ISOTILE_HEIGHT		(MAPTOOL_TILESIZE*2)

#define ISOTILE_HALF_WIDTH	(MAPTOOL_TILESIZE*2)
#define ISOTILE_HALF_HEIGHT	(MAPTOOL_TILESIZE)

#define ISOTILEX			(MAPTOOL_TILEVIEWX/2)
#define ISOTILEY			(MAPTOOL_TILEVIEWY)
//~����-----------------------------------------------------------------

//���Ӹ�----------------------------------------------------------------
#define GAMEMAP_TILESIZE		32

#define GAMEMAP_TILEVIEWX		20
#define GAMEMAP_TILEVIEWY		12 //30



//~���Ӹ�---------------------------------------------------------------


//��Ʈ�ʵ� Ÿ�� �Ӽ�
#define ATTR_UNMOVE		0x00000001	//


#define HIGHTDIRT_LF  0x0001
#define HIGHTDIRT_RG  0x0002
#define HIGHTDIRT_UP  0x0004
#define HIGHTDIRT_DN  0x0008


//��Ÿ�Ͽ� �� �ͷ��μӼ�
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

//�ʿ����Ϳ��� ������ �ͷ��� ����
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
	FOGLEVEL_BLACK,		//����ȭ��
	FOGLEVEL_GRAY,		//������ Ȯ���ߴ� �þ�
	FOGLEVEL_VIEW,		//���� �þ�
	FOGLEVEL_DETECT,	//����Ʈ ���� �þ�

};

//Ÿ�� ����ü
struct tagTile
{
	DWORD	terrain;	//�ͷ���
	POINT	terrainNum;		//�ͷ��� �ε���

	DWORD	obj;			//
	UINT	nrAmount;//NeutralResource �ڿ���

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