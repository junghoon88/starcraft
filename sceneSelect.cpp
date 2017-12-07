#include "stdafx.h"
#include "sceneSelect.h"


sceneSelect::sceneSelect()
{
	for (int i = 0; i < BTNMENU_MAX; i++)
	{
		_btn[i] = NULL;
	}
}


sceneSelect::~sceneSelect()
{
}

HRESULT sceneSelect::init(void)
{
	_btn[BTNMENU_GAMESTART] = new button;
	_btn[BTNMENU_GAMESTART]->init(L"버튼1", L"게임시작", 100, 100, { 0,0 }, { 0,1 }, cbFuncGameStart, this);
	_btn[BTNMENU_MAPTOOL] = new button;
	_btn[BTNMENU_MAPTOOL]->init(L"버튼1", L"맵에디터",	100, 200, { 0,0 }, { 0,1 }, cbFuncMaptool, this);
	_btn[BTNMENU_EXIT] = new button;
	_btn[BTNMENU_EXIT]->init(L"버튼1", L"나가기",		100, 300, { 0,0 }, { 0,1 }, cbFuncGameExit, this);

	return S_OK;
}


void sceneSelect::release(void)
{
	for (int i = 0; i < BTNMENU_MAX; i++)
	{
		SAFE_DELETE(_btn[i]);
	}
}

void sceneSelect::update(void)
{
	for (int i = 0; i < BTNMENU_MAX; i++)
	{
		_btn[i]->update();
	}
}

void sceneSelect::render(void)
{
	for (int i = 0; i < BTNMENU_MAX; i++)
	{
		_btn[i]->render();
	}
}

//callback functions
void sceneSelect::cbFuncGameStart(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
}
void sceneSelect::cbFuncMaptool(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	ss->setChangeScene(true, L"맵툴씬");
	//SCENEMANAGER->changeScene();
}
void sceneSelect::cbFuncGameExit(void* obj)
{
	sceneSelect* ss = (sceneSelect*)obj;
	PostQuitMessage(0);
}
