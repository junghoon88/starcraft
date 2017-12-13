#include "stdafx.h"
#include "gameNode.h"
#include "image.h"

//빈 비트맵 파일 백버퍼 생성
static image* _backBuffer = IMAGEMANAGER->addImage(L"backBuffer", WINSIZEX, WINSIZEY);

gameNode::gameNode()
{
	_changeScene = false;
	_tcscpy(_strNextSceneName, L"");
}


gameNode::~gameNode()
{

}

HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TXTDATA->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		DATABASE->init();
		MAINCAMERA->init();
		RENDERMANAGER->init();
		//EDITBOXMANAGER->init();
	}

	return S_OK;
}

void gameNode::release(void)
{
	if (_managerInit)
	{
		KEYMANAGER->release();					KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();				IMAGEMANAGER->releaseSingleton();
		TXTDATA->release();						TXTDATA->releaseSingleton();
		TIMEMANAGER->release();					TIMEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();				SOUNDMANAGER->releaseSingleton();
		EFFECTMANAGER->release();				EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->release();				SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->release();				KEYANIMANAGER->releaseSingleton();
		DATABASE->release();					DATABASE->releaseSingleton();
		MAINCAMERA->release();					MAINCAMERA->releaseSingleton();
		RENDERMANAGER->release();				RENDERMANAGER->releaseSingleton();
		//EDITBOXMANAGER->release();				EDITBOXMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update(void)	
{
	//InvalidateRect(_hWnd, NULL, false);
	SOUNDMANAGER->update();

}

void gameNode::render(void)
{

}

void gameNode::getChar(WPARAM wParam)
{

}

void gameNode::checkScene(void)
{
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		case WM_CREATE:
		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
		case WM_KEYDOWN:
		break;
		case WM_CHAR:
			this->getChar(wParam);
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


image* gameNode::getBackBuffer(void) { return _backBuffer; }
HDC gameNode::getMemDC(void) { return _backBuffer->getMemDC(); }
