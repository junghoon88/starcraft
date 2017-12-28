#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#include "editbox.h"

#define SIDEWINDOW_STARTX (MAPTOOL_TILEVIEWX * TILESIZE)

#define TERRAINNUM_HIGHDIRT_LF	0x0010
#define TERRAINNUM_HIGHDIRT_RG	0x0020
#define TERRAINNUM_HIGHDIRT_UP	0x0040
#define TERRAINNUM_HIGHDIRT_DN	0x0080


enum BTNCTRL
{
	BTNCTRL_SAVE,
	BTNCTRL_LOAD,
	BTNCTRL_EXIT,

	BTNCTRL_MAX
};

enum SAMPLETERRAIN
{
	SAMPLETERRAIN_NONE = -1,
	SAMPLETERRAIN_DIRT,
	SAMPLETERRAIN_HIGTDIRT,
	SAMPLETERRAIN_WATER,

	SAMPLETERRAIN_MAX
};

enum SAMPLEOBJECT
{
	SAMPLEOBJECT_NONE = -1,
	SAMPLEOBJECT_MINERAL,
	SAMPLEOBJECT_GAS,
	SAMPLEOBJECT_PLAYER1,
	SAMPLEOBJECT_PLAYER2,

	SAMPLEOBJECT_ERASER,

	SAMPLEOBJECT_MAX
};

struct tagDragInfo
{
	int x;
	int y;
	int a;
	int b;
};

enum OBJSTATE
{
	OBJSTATE_NONE,		//������Ʈ ����
	OBJSTATE_PLACEABLE,	//������Ʈ ��ġ�� �� ����
	OBJSTATE_OVERLAP,	//������Ʈ ��ġ�Ұ�(��ħ)
};

class sceneMaptool : public gameNode
{
private:
	//Ÿ��
	tagTile			_tiles[TILEX][TILEY];				//Ÿ��
	image*			_imgTiles[TILEX][TILEY];			//Ÿ�� �̹���
	BOOL			_isChangedTile[TILEX][TILEY];		//Ÿ�� ���� ���� ����

	//���콺 ����
	POINT			_cursorPt;		//ī�޶� ��ġ ����� ���콺 ��ġ
	POINT			_cursorTile;	//ī�޶� ��ġ ����� ���콺 ��ġ�� Ÿ�� ��ȣ
	POINT			_isoCursor;		//ISOŸ�� ǥ�ÿ� Ŀ�� ��ġ 

	//�ͷ���, ������Ʈ
	SAMPLETERRAIN	_curTerrain;									//���� ������ �ͷ���
	SAMPLEOBJECT	_curObject;										//���� ������ ������Ʈ
	RECT			_rcSelectTerrain[SAMPLETERRAIN_MAX];			//���ð����� �ͷ��� rect
	image*			_imgSelectTerrain[SAMPLETERRAIN_MAX];			//���ð����� �ͷ��� image
	RECT			_rcSelectObject[SAMPLEOBJECT_MAX];				//���ð����� ������Ʈ rect
	image*			_imgSelectObject[SAMPLEOBJECT_MAX];				//���ð����� ������Ʈ image
	editbox*		_editboxNrAmount;								//�ڿ����� �Է¿� editbox
	image*			_imgObject;										//������ ������Ʈ ���콺�� �����ֱ�� �̹���
	OBJSTATE		_objState[OBJECTSIZE_MAX_X][OBJECTSIZE_MAX_Y];	//������Ʈ �ִ� ũ��� 4,3����

	BOOL			_isLocatedP1;
	BOOL			_isLocatedP2;

	//��Ÿ�� ���콺 ó��
	BOOL			_isClicked;
	BOOL			_endDrag;
	POINT			_startIso;
	POINT			_endIso;
	vector<tagDragInfo>	_vDragInfo;
	


	//minimap
	image*		_imgMiniMap;
	RECT		_rcMiniMap;
	RECT		_rcMiniMapCamera;
	COLORREF	_colorMiniMap[TILEX][TILEY];

	//��ư
	button* _btnCtrl[BTNCTRL_MAX];


public:
	sceneMaptool();
	~sceneMaptool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);


private:
	void initButtons(void);
	void initTiles(void);
	void initMiniMap(void);
	void initSampleTerrainObject(void);

	//update
	void updateCamera(void);
	void calcMouseRealPosition(void);
	void selectTerrainObject(void);
	void calcIsoTile(void);
	void clickIsoTile(void);
	void dragIsoTile(void);
	bool calcObjectTile(void);
	void clickObjectTile(void);
	void eraseObject(int tilex, int tiley);
	POINT findObjectStartPoint(int tilex, int tiley);



	void setDirt(int cx, int cy);
	void setHighDirt(void);
	void setHighDirtEdge(int cx, int cy, DWORD edge);
	void setWater(void);

	void updateTileImage(void);
	void setTileImageAll(void);
	void updateMiniMap(void);


	void saveData(const TCHAR* fileName);
	void loadData(const TCHAR* fileName);
	void saveFile(void);
	void loadFile(void);

	//render
	void renderTiles(void);
	void renderDragingIsoTiles(void);
	void renderCurIsoTile(void);
	void renderObject(void);
	void renderSideWindow(void);
	void renderMiniMap(void);


private:
	//button callbackFunction
	static void cbButtonSave(void* obj);
	static void cbButtonLoad(void* obj);
	static void cbButtonExit(void* obj);

};

