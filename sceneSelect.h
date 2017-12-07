#pragma once
#include "gameNode.h"
#include "button.h"

enum BTNMENU
{
	BTNMENU_GAMESTART,
	BTNMENU_MAPTOOL,
	BTNMENU_EXIT,

	BTNMENU_MAX
};

class sceneSelect : public gameNode
{
private:
	button* _btn[BTNMENU_MAX];
	
public:
	sceneSelect();
	~sceneSelect();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	//button callbackFunction
public:
	//level1
	static void cbFuncGameStart(void* obj);
	static void cbFuncMaptool(void* obj);
	static void cbFuncGameExit(void* obj);

};

