#include "stdafx.h"
#include "DxWindow.h"
#include "mainGame.h"

HINSTANCE _hInstance;		//���� ������ȣ
HWND _hWnd;
POINT _ptMouse;
POINT _mainCamera = { 0, 0 };

//Window
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DxWindow::getDxWindow()->MessageLoop(hWnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance; //image ���� ������ �߰���

	mainGame main(hInstance, L"DxClass", lpszCmdParam, nCmdShow);
	main.Create(L"starcraft");
	main.CreateDevice();
	main.init();

	WPARAM wParam = main.Run();

	main.release();


	//PrintText::DeleteInstance();
	//Keyboard::DeleteInstance();

	return wParam;
}

//DxWindow
DxWindow* DxWindow::dxWindow = NULL;
LPDIRECT3D9 DxWindow::d3d = NULL;
LPDIRECT3DDEVICE9 DxWindow::device = NULL;

int DxWindow::_stage = 1;


//��ü ������
DxWindow::DxWindow(HINSTANCE hInstance, LPCWSTR lpClassName, LPCSTR lpszCmdParam, int nCmdShow)
	: _managerInit(false)
{
	dxWindow = this;

	commandShow = nCmdShow;
	instance = hInstance;
	handle = NULL;

	srand(time(NULL));

	if (lpClassName != NULL)
	{
		int length = wcslen(lpClassName) + 1;

		className = new WCHAR[length];
		wcscpy_s(className, length, lpClassName);
	}
	else
	{
		className = NULL;
	}

	if (lpszCmdParam != NULL)
	{
		int length = strlen(lpszCmdParam) + 1;

		commandLine = new char[length];
		strcpy_s(commandLine, length, lpszCmdParam);
	}
	else
	{
		commandLine = NULL;
	}
}

DxWindow::DxWindow()
{

}

//��ü �Ҹ���
DxWindow::~DxWindow()
{

}

//virtual
void DxWindow::init() {}

void DxWindow::Create(LPCWSTR title)
{
	WNDCLASS wndClass;

	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = instance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = className;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	ATOM result = RegisterClass(&wndClass);
	assert(result != 0);

	RECT rect;
	SetRect(&rect, 0, 0, winSize.x, winSize.y);
	AdjustWindowRect(&rect, winStyle, FALSE);

	int sysWidth = GetSystemMetrics(SM_CXSCREEN);
	int sysHeight = GetSystemMetrics(SM_CYSCREEN);

	handle = CreateWindow
	(
		className
		, title
		, winStyle
		, (sysWidth - (rect.right - rect.left)) / 2
		, (sysHeight - (rect.bottom - rect.top)) / 2
		, (rect.right - rect.left)
		, (rect.bottom - rect.top)
		, NULL
		, NULL
		, instance
		, NULL
	);
	assert(handle != NULL);
}

void DxWindow::CreateDevice(void)
{
	D3DPRESENT_PARAMETERS d3dParam;
	ZeroMemory(&d3dParam, sizeof(d3dParam));

	d3dParam.Windowed = isWindow;
	d3dParam.SwapEffect = D3DSWAPEFFECT_DISCARD; //�ø��� ����ۿ� ������ ���� �ʴ´�.
	d3dParam.EnableAutoDepthStencil = TRUE; //���� ���ٽ� ���� �ڵ� ����
	d3dParam.AutoDepthStencilFormat = D3DFMT_D16; //���� ����

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	assert(d3d != NULL);

	D3DCAPS9 caps;
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	HRESULT hr = d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT, //����Ʈ ����� ����
		D3DDEVTYPE_HAL, //����Ʈ����� �ϵ���� ���� ������ ���
		handle, //������ �ڵ�
		D3DCREATE_HARDWARE_VERTEXPROCESSING, //���ؽ� ������ �ϵ����� ó��
		&d3dParam, &device
	);
	assert(SUCCEEDED(hr));

	ShowWindow(handle, SW_SHOW); //������ �����ֱ�
	UpdateWindow(handle); //������ ����
	ShowCursor(isShowCursor); //Ŀ�� ����
}


/**-----------------------------------------------------------------------------
* ��� ����
*------------------------------------------------------------------------------
*/
void DxWindow::SetupMatrices()
{
	/// �������
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matWorld, timeGetTime() / 1000.0f);
	device->SetTransform(D3DTS_WORLD, &matWorld);

	/// ������� ����
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 vLookatPt((float)_mainCamera.x, (float)_mainCamera.y, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	device->SetTransform(D3DTS_VIEW, &matView);

	/// �������� ��� ����
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, &matProj);
}

WPARAM DxWindow::Run(void)
{
	MSG message;
	ZeroMemory(&message, sizeof(message));

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);

			SOUNDMANAGER->update();

			update();


			device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);
			device->BeginScene();

			//SetupMatrices();


			render();

			device->EndScene();
			device->Present(0, 0, 0, 0);
		}
	}


	UnregisterClass(className, instance);
	return message.wParam;
}

LRESULT DxWindow::MessageLoop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_MOUSEMOVE:
			_ptMouse.x = (LONG)(static_cast<float>LOWORD(lParam));
			_ptMouse.y = (LONG)(static_cast<float>HIWORD(lParam));
			break;

		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				SendMessage(hwnd, WM_DESTROY, 0, 0);
				PostQuitMessage(0);
				break;
			}

			return 0;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void DxWindow::initialize(void)
{
	_managerInit = true;

	//singleton init
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	//TXTDATA->init();
	TIMEMANAGER->init();
	SOUNDMANAGER->init();
	//EFFECTMANAGER->init();
	SCENEMANAGER->init();
	KEYANIMANAGER->init();
	DATABASE->init();
	MAINCAMERA->init();
	//RENDERMANAGER->init();
	//TEXTMANAGER->init() --> ����Ҷ����� �ʱ�ȭ�ؼ� ����Ѵ�.
	RECTMANAGER->init();
}

void DxWindow::releaseSingleton(void)
{
	//singleton release
	if (_managerInit)
	{
		KEYMANAGER->release();					KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();				IMAGEMANAGER->releaseSingleton();
		//TXTDATA->releaseSingleton();
		TIMEMANAGER->release();					TIMEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();				SOUNDMANAGER->releaseSingleton();
		//EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->release();				SCENEMANAGER->releaseSingleton();

		KEYANIMANAGER->release();				KEYANIMANAGER->releaseSingleton();
		DATABASE->release();					DATABASE->releaseSingleton();
		MAINCAMERA->release();					MAINCAMERA->releaseSingleton();
		//RENDERMANAGER->releaseSingleton();
		
		TEXTMANAGER->release();					TEXTMANAGER->releaseSingleton();
		RECTMANAGER->release();					RECTMANAGER->releaseSingleton();
	}

	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);

	if (handle != NULL)
		DestroyWindow(handle);

	SAFE_DELETE_ARRAY(className);
	SAFE_DELETE_ARRAY(commandLine);
}

