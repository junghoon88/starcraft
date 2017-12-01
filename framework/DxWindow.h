#pragma once

class DxWindow
{
private:
	bool _managerInit;


protected:
	static DxWindow* dxWindow;

	HINSTANCE instance;
	LPWSTR className;
	LPSTR commandLine;
	int commandShow;

	HWND handle;

	POINT winSize = { WINSIZEX, WINSIZEY };
	DWORD winStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	BOOL isWindow = TRUE;
	BOOL isShowCursor = TRUE;

	static LPDIRECT3D9 d3d;
	static LPDIRECT3DDEVICE9 device;

	void initialize(void);
	void releaseSingleton(void);

	//스테이지를 전역으로 선언
	static int _stage;


public:
	//객체 생성자
	DxWindow(HINSTANCE hInstance, LPCWSTR lpClassName, LPCSTR lpszCmdParam, int nCmdShow);
	DxWindow();
	//객체 소멸자
	~DxWindow();

	static DxWindow* getDxWindow(void) { return dxWindow; }
	static LPDIRECT3D9 getD3D(void) { return d3d; }
	static LPDIRECT3DDEVICE9 getDevice(void) { return device; }

	void Create(LPCWSTR title);
	void CreateDevice(void);

	WPARAM Run(void);
	void SetupMatrices();

	LRESULT MessageLoop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	virtual void init(void);
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	static int getStage(void) { return _stage; }
	static void setStage(int stage) { _stage = stage; }
};