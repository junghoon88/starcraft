#pragma once
#include "stdafx.h"

//Ÿ�� ����
#define TILEX		128
#define TILEY		128

//����-----------------------------------------------------------------
//�� Ÿ���� �԰�
#define MAPTOOL_TILESIZE	32

//���Ӹ�, �������� ������ Ÿ�� ����
#define MAPTOOL_TILEVIEWX	20
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
#define ATTR_INCASTLE	0x00000001	//

//��Ÿ�Ͽ� �� �ͷ��μӼ�
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

//������Ʈ ����
enum OBJECTSELECT
{
	OBJECTSELECT_NONE = -1,
	
	OBJECTSELECT_MAX
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
	TERRAIN terrain;	//�ͷ���
	INT terrainNum;		//�ͷ��� �ε���

	DWORD obj;			//
	RECT rc;			//

	BOOL isClick;		//������Ʈ ����
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