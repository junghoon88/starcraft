#include "stdafx.h"
#include "mainGame.h"
#include "globalTools.h"
#include "gameController.h"

#include <process.h>


//���������� �����Ѵٸ� ������ 
HINSTANCE _hInstance;		//���� ������ȣ
HWND _hWnd;					//������
POINT _ptMouse;
HFONT _gFont[FONTVERSION_MAX];
HBRUSH _gBrush[BRUSHVERSION_MAX];
HPEN _gPen[PENVERSION_MAX];


LPTSTR _lpszClass = WINNAME;


mainGame _mg;
globalTools _gTools;


gameController	_gc;
unsigned int	_gcId;

BOOL			_gameExit = FALSE;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;			//�޼���
	WNDCLASS wndClass;		//������ ������ ���� ����ü

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸� 
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� 
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = _lpszClass;							//������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ â ��Ÿ��

	//������ ���� ���
	RegisterClass(&wndClass);

	//������ â ��������
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,		//������ â ��Ÿ��
		WINSTARTX,					//������ ���� ��ǥ X
		WINSTARTY,					//������ ���� ��ǥ Y
		WINSIZEX,					//������ â ����ũ��
		WINSIZEY,					//������ â ����ũ��
		NULL,						//�θ� ������ ��뿩��
		(HMENU)NULL,				//�޴� ��뿩��
		hInstance,					//�ν��Ͻ�
		NULL);						//�ڽ� ������ ��뿩��

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//������ â�� ����Ϳ� �����
	ShowWindow(_hWnd, cmdShow);

	if (FAILED(_mg.init()))
	{
		return 0;
	}

	//Font, Brush ����
	_gTools.setFontAll();
	_gTools.setBrushAll();
	_gTools.setPenAll();


	//GetMessage : �޽��� ������ ������ �׶� ����
	//PeekMessage : �޽��� ������ ������ ���� ������ ����(��� ������������)
	while (true)
	{
		if (_mg.getStop())
		{
			setWindowsSize(WINSTARTX, WINSTARTY, _mg.getWinSize().x, _mg.getWinSize().y);

			//������ â�� ����Ϳ� �����
			ShowWindow(_hWnd, cmdShow);
			
			_mg.setStop(false);
		}

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				_gameExit = TRUE;
				break;
			}
			TranslateMessage(&message);	//�Է��� ������ ���� �� �޽��� ó�� ���
			DispatchMessage(&message);	//������ �����쿡 �� �޽��� ����
		}
		else
		{
			TIMEMANAGER->update(_mg.getFPS());

			DWORD tick1 = GetTickCount();

			_mg.update();
			_mg.render();
			_mg.checkScene();

			DWORD tick2 = GetTickCount();
			DWORD tick = tick2 - tick1;

			if (tick > 10)
			{
				printf("");

			}
			if (tick > 40)
			{
				printf("");

			}
			if (tick > 80)
			{
				printf("");

			}

		}
	}

	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);	//�Է��� ������ ���� �� �޽��� ó�� ���
	//	DispatchMessage(&message);	//������ �����쿡 �� �޽��� ����
	//}

	_mg.release();

	//Font, Brush ����
	_gTools.deleteFontAll();
	_gTools.deleteBrushAll();
	_gTools.deletePenAll();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;
	
	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}

