#pragma once
#include "stdafx.h"


//�� Ÿ���� �԰�
#define TILESIZE	32

//Ÿ�� ����
#define TILEX		128
#define TILEY		128

//���Ӹ�, �ʿ����Ϳ��� ������ Ÿ�� ����
#define TILEVIEWX	30
#define TILEVIEWY	30

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
	OBJECTSELECT_ENEMY,
	OBJECTSELECT_AILY,
	OBJECTSELECT_PLAYER,

	OBJECTSELECT_MAX
};

//Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;
	TCHAR obj[128];
	RECT rc;

	INT terrainNum;		//���� �ͷ��� �ε���
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
