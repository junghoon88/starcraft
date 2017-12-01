#pragma once
class PrintText
{
private:

	LPD3DXFONT font;
	LPD3DXSPRITE sprite;

	wstring data;

public:
	static LPDIRECT3DDEVICE9 device;

public:
	PrintText(LPDIRECT3DDEVICE9 device);
	~PrintText();

	void SetFont(INT height, LPCWSTR fontName);
	void AddText(wstring value);

	void Render(RECT &rcText, COLORREF color);
};

