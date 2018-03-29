#pragma once
#include "gameNode.h"
#include "button.h"

enum BTNMENU
{
	//LEVEL1
	BTNMENU_GAMESELECT,
	BTNMENU_MAPTOOL,
	BTNMENU_EXIT,

	//LEVEL2
	BTNMENU_START,
	BTNMENU_BACK,


	BTNMENU_MAX
};

enum SELECTLEVEL
{
	SELECTLEVEL1,
	SELECTLEVEL2,
};

enum FADE
{
	FADE_NONE,
	FADE_TO_LEVEL1,
	FADE_TO_LEVEL2,
};

struct tagMapFileInfo
{
	RECT rc;
	TCHAR str[100];
	bool clicked;
};


class sceneSelect : public gameNode
{
private:
	SELECTLEVEL	_level;

	button*		_btn[BTNMENU_MAX];

	image*		_imgBackground1;
	image*		_imgBackground2;

	//fade
	image*		_imgFade;
	FADE		_fading;
	FLOAT		_fadeTime;
	BYTE		_alpha;
	int			_dir;

	//file
	image*		_imgMapList;
	RECT		_rcMapList;
	//RECT		_rcMinimap;
	image*		_imgMinimap;

	UINT		_tempnum;

	vector<tagMapFileInfo>	_vMapFileInfo;

public:
	sceneSelect();
	~sceneSelect();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void gameStart(void);

private:
	void loadMapFiles(void);
	int findSelectIndex(void);

	//button callbackFunction
public:
	//level1
	static void cbFuncGameSelect(void* obj);
	static void cbFuncMaptool(void* obj);
	static void cbFuncGameExit(void* obj);
	static void cbFuncStart(void* obj);
	static void cbFuncBack(void* obj);

public:
	inline void goNextLevel(void) { _fading = FADE_TO_LEVEL2; }
	inline void goPrevLevel(void) { _fading = FADE_TO_LEVEL1; }


};

