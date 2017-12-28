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
	OBJSTATE_NONE,		//오브젝트 없음
	OBJSTATE_PLACEABLE,	//오브젝트 설치할 수 있음
	OBJSTATE_OVERLAP,	//오브젝트 설치불가(겹침)
};

class sceneMaptool : public gameNode
{
private:
	//타일
	tagTile			_tiles[TILEX][TILEY];				//타일
	image*			_imgTiles[TILEX][TILEY];			//타일 이미지
	BOOL			_isChangedTile[TILEX][TILEY];		//타일 정보 변경 여부

	//마우스 관련
	POINT			_cursorPt;		//카메라 위치 적용된 마우스 위치
	POINT			_cursorTile;	//카메라 위치 적용된 마우스 위치의 타일 번호
	POINT			_isoCursor;		//ISO타일 표시용 커서 위치 

	//터레인, 오브젝트
	SAMPLETERRAIN	_curTerrain;									//현재 선택한 터레인
	SAMPLEOBJECT	_curObject;										//현재 선택한 오브젝트
	RECT			_rcSelectTerrain[SAMPLETERRAIN_MAX];			//선택가능한 터레인 rect
	image*			_imgSelectTerrain[SAMPLETERRAIN_MAX];			//선택가능한 터레인 image
	RECT			_rcSelectObject[SAMPLEOBJECT_MAX];				//선택가능한 오브젝트 rect
	image*			_imgSelectObject[SAMPLEOBJECT_MAX];				//선택가능한 오브젝트 image
	editbox*		_editboxNrAmount;								//자원수량 입력용 editbox
	image*			_imgObject;										//선택한 오브젝트 마우스에 보여주기용 이미지
	OBJSTATE		_objState[OBJECTSIZE_MAX_X][OBJECTSIZE_MAX_Y];	//오브젝트 최대 크기는 4,3으로

	BOOL			_isLocatedP1;
	BOOL			_isLocatedP2;

	//맵타일 마우스 처리
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

