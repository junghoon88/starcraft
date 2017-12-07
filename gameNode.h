#pragma once
//#include "image.h"

//��ȣ���������� ���漱������ �ٲ�
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

	virtual HRESULT init(void);	//�ʱ�ȭ
	virtual HRESULT init(bool managerInit);
	virtual void release(void);	//�޸� ����
	virtual void update(void);	//�������(Ÿ�̸�)
	virtual void render(void);	//�׷��ִ� �Լ�
	virtual void getChar(WPARAM wParam);
	virtual void checkScene(void);

public:
	image* getBackBuffer(void);
	HDC getMemDC(void);
	HDC getHDC(void) { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);


	
public:
	//changeScene ����
	inline void setChangeScene(BOOL changeScene, TCHAR* strNextSceneName)
	{
		_changeScene = changeScene;
		_tcscpy(_strNextSceneName, strNextSceneName);
	}
	inline BOOL getChangeScene(void) { return _changeScene; }
	inline TCHAR* getChanageSceneInfo(void) { return _strNextSceneName; }
};

