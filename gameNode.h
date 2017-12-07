#pragma once
#include "image.h"

//빈 비트맵 파일 백버퍼 생성
static image* _backBuffer = IMAGEMANAGER->addImage(L"backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);	//초기화
	virtual HRESULT init(bool managerInit);
	virtual void release(void);	//메모리 해제
	virtual void update(void);	//연산관련(타이머)
	virtual void render(void);	//그려주는 함수
	virtual void getChar(WPARAM wParam);

	image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

