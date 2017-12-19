#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#include "editbox.h"

#define SIDEWINDOW_STARTX (MAPTOOL_TILEVIEWX * MAPTOOL_TILESIZE)

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

	SAMPLEOBJECT_MAX
};

struct tagDragInfo
{
	int x;
	int y;
	int a;
	int b;
};

class sceneMaptool : public gameNode
{
private:
	//타일
	tagTile			_tiles[TILEX][TILEY];				//타일
	image*			_imgTiles[TILEX][TILEY];			//타일 이미지
	BOOL			_isChangedTile[TILEX][TILEY];		//타일 정보 변경 여부

	//ISO타일
	//tagisoTile _isoTile[ISOTILEX][ISOTILEY];	//X : 왼쪽아래로, Y:오른쪽아래로
	POINT			_isoCursor;

	SAMPLETERRAIN	_curTerrain;
	RECT			_rcSelectTerrain[SAMPLETERRAIN_MAX];
	SAMPLEOBJECT	_curObject;

	BOOL			_isClicked;
	BOOL			_endDrag;
	POINT			_startIso;
	POINT			_endIso;
	vector<tagDragInfo>	_vDragInfo;
	


	//minimap
	image*	_imgMiniMap;
	RECT	_rcMiniMap;
	RECT	_rcMiniMapCamera;

	//버튼
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
	void initIsoTiles(void);
	void initMiniMap(void);


	void updateCamera(void);
	void selectTerrain(void);
	void calcIsoTile(void);
	void clickIsoTile(void);

	void setDirt(void);
	void setHighDirt(void);
	void setHighDirtEdge(int cx, int cy, DWORD edge);

	void updateTileImage(void);
	void setTileImageAll(void);


	void saveData(const TCHAR* fileName);
	void loadData(const TCHAR* fileName);
	void saveFile(void);
	void loadFile(void);

	void renderTiles(void);
	void renderDragingIsoTiles(void);
	void renderCurIsoTile(void);
	void renderSideWindow(void);
	
	void renderMiniMap(void);


private:
	//button callbackFunction
	static void cbButtonSave(void* obj);
	static void cbButtonLoad(void* obj);
	static void cbButtonExit(void* obj);

};

