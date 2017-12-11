#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"

enum BTNCTRL
{
	BTNCTRL_SAVE,
	BTNCTRL_LOAD,

	BTNCTRL_MAX
};

class sceneMaptool : public gameNode
{
private:
	//타일
	tagTile _tiles[TILEX][TILEY];				//타일
	image*	_imgTiles[TILEX][TILEY];			//타일 이미지
	BOOL	_isChangedTile[TILEX][TILEY];		//타일 정보 변경 여부

	//ISO타일
	//tagisoTile _isoTile[ISOTILEX][ISOTILEY];	//X : 왼쪽아래로, Y:오른쪽아래로
	POINT _isoCursor;


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

	void clickIsoTile(void);

	void updateTileImage(void);
	void setTileImageAll(void);


	void saveData(void);
	void loadData(void);

	void renderTiles(void);

private:
	//button callbackFunction
	static void cbButtonSave(void* obj);
	static void cbButtonLoad(void* obj);

};

