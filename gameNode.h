#pragma once
//#include "image.h"

//상호참조때문에 전방선언으로 바꿈
class image;

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

	BOOL	_changeScene;
	TCHAR	_strNextSceneName[128];


public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init(void);	//초기화
	virtual HRESULT init(bool managerInit);
	virtual void release(void);	//메모리 해제
	virtual void update(void);	//연산관련(타이머)
	virtual void render(void);	//그려주는 함수
	virtual void getChar(WPARAM wParam);
	virtual void checkScene(void);

public:
	image* getBackBuffer(void);
	HDC getMemDC(void);
	HDC getHDC(void) { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);


	
public:
	//changeScene 수정
	inline void setChangeScene(BOOL changeScene, TCHAR* strNextSceneName)
	{
		_changeScene = changeScene;
		_tcscpy(_strNextSceneName, strNextSceneName);
	}
	inline BOOL getChangeScene(void) { return _changeScene; }
	inline TCHAR* getChanageSceneInfo(void) { return _strNextSceneName; }
};

