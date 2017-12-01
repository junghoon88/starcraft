#pragma once
#include "singletonBase.h"

class PrintText;
class textManager : public singletonBase<textManager>
{
private:
	typedef map<wstring, PrintText*> mText;
	typedef map<wstring, PrintText*>::iterator miText;

	mText _mText;

public:
	textManager();
	~textManager();

	void init(LPDIRECT3DDEVICE9 device, wstring strKey);
	void release(void);
	void addText(wstring strKey, wstring strText);
	void setFont(wstring strKey, int height, LPCWSTR fontName);
	void render(wstring strKey, RECT &rcText, COLORREF color = RGB(0, 0, 0));
};

