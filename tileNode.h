#pragma once
#include "stdafx.h"

//Ÿ�� ����
#define TILEX		128
#define TILEY		128

//�� Ÿ���� �԰�
#define TILESIZE	32

//����-----------------------------------------------------------------
//�������� ������ Ÿ�� ����
#define MAPTOOL_TILEVIEWX	15 //20 �� �ִ�ũ��
#define MAPTOOL_TILEVIEWY	15

//���� ISOTILE
#define ISOTILE_WIDTH		(TILESIZE*4)
#define ISOTILE_HEIGHT		(TILESIZE*2)

#define ISOTILE_HALF_WIDTH	(TILESIZE*2)
#define ISOTILE_HALF_HEIGHT	(TILESIZE)
//~����-----------------------------------------------------------------

//���Ӹ�----------------------------------------------------------------
//���Ӹʿ��� ������ Ÿ�� ����
#define GAMEMAP_TILEVIEWX		20
#define GAMEMAP_TILEVIEWY		12 //30



//~���Ӹ�---------------------------------------------------------------


//��Ʈ�ʵ� Ÿ�� �Ӽ�
#define ATTR_UNMOVE		0x00000001	//
#define ATTR_UNBUILD	0x00000002	//
#define ATTR_CREEP		0x00000004



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

enum OBJECT
{
	OBJECT_NONE, 

	//�ڿ�(�̳׶�, ����)
	OBJECT_MINERAL1_START,	//�̳׶��� (0,0)��ġ
	OBJECT_MINERAL1_BODY,	//�̳׶��� �����ϴ� (0,0) ���� ��ġ
	OBJECT_MINERAL2_START,	//�̳׶��� �̹����� �� 3����(������ġ)
	OBJECT_MINERAL2_BODY,	//
	OBJECT_MINERAL3_START,	//
	OBJECT_MINERAL3_BODY,	//
	OBJECT_GAS_START,		//������ (0,0)��ġ
	OBJECT_GAS_BODY,		//������ �����ϴ� (0,0) ���� ��ġ

	//�÷��̾� ������ġ
	OBJECT_LOCATION_P1_START,		//�÷��̾� ������ġ (0,0)��ġ
	OBJECT_LOCATION_P1_BODY,		//�÷��̾� ������ġ (0,0)���� ��ġ
	OBJECT_LOCATION_P2_START,		//
	OBJECT_LOCATION_P2_BODY,		//
	
	//��������� ���������� ���

	//������ʹ� ���Ӹʿ��� �߰��� �� ����

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
	DWORD	terrain;		//�ͷ���
	POINT	terrainNum;		//�ͷ��� �ε���

	DWORD	obj;			//
	UINT	nrAmount;		//NeutralResource �ڿ���

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