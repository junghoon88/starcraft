#pragma once
#include "singletonBase.h"
#include "Rect.h"

class rectManager : public singletonBase<rectManager>
{
private:
	typedef map<wstring, Rect*> mRectList;
	typedef map<wstring, Rect*>::iterator mRectiter;

	mRectList _mRectList;

public:
	rectManager();
	~rectManager();

	void init(void);
	void release(void);

	Rect* addRect(LPDIRECT3DDEVICE9 device, wstring strKey, D3DXVECTOR2 coord, D3DXVECTOR2 size, COLORREF color = RGB(0, 0, 0), BYTE alpha = 255);
	BOOL deleteAll(void);

	Rect* findRect(wstring strKey);


	void render(wstring strKey, bool cameraOffset = true);
	RECT getRect(wstring strKey);

	void setCoord(wstring strKey, float x, float y);
	void setSize(wstring strKey, float x, float y);
	void setScale(wstring strKey, float x, float y);
	void setRotate(wstring strKey, float angleDeg);
	void setCenterPer(wstring strKey, float x, float y); //size 기준 배율로
	void setCenterPos(wstring strKey, float x, float y); //position
	void setColor(wstring strKey, COLORREF color, BYTE alpha);
	void move(wstring strKey, float moveX, float moveY);

};

