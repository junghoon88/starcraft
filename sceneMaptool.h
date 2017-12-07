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
	tagTile _tiles[TILEX][TILEY];
	image*	_imgTiles[TILEX][TILEY];

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
	void updateTileImage(void);

	void saveData(void);
	void loadData(void);

private:
	//button callbackFunction
	static void cbButtonSave(void* obj);
	static void cbButtonLoad(void* obj);

};

