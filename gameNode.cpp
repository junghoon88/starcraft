#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
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
		//SetTimer(_hWnd, 1, 10, NULL);
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
		//KillTimer(_hWnd, 1);
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


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		//������ â�� �������� ������ �Ǵ� �Լ�
		case WM_CREATE:

		break;
		//case WM_PAINT:
		//{
		//	hdc = BeginPaint(hWnd, &ps);

		//	this->render();

		//	EndPaint(hWnd, &ps);
		//}
		//break;
		//case WM_TIMER:
		//	this->update();
		//break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;
		case WM_CHAR:
			this->getChar(wParam);
		break;
		case WM_DESTROY:
		//������ â ���� �Լ�
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}