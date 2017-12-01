#include "stdafx.h"
#include "PrintText.h"

LPDIRECT3DDEVICE9 PrintText::device = NULL;

PrintText::PrintText(LPDIRECT3DDEVICE9 device)
	: data(L"")
{
	this->device = device;

	HRESULT hr = D3DXCreateFont(device,
		12, 0, 0, 1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"µ¸¿ò",
		&font);
	assert(hr == S_OK);

	hr = D3DXCreateSprite(device, &sprite);
	assert(hr == S_OK);

}


PrintText::~PrintText()
{
	SAFE_RELEASE(font);
	SAFE_RELEASE(sprite);
}

void PrintText::SetFont(INT height, LPCWSTR fontName)
{
	HRESULT hr = D3DXCreateFont(device,
		height, 0, 0, 1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		fontName,
		&font);
	assert(hr == S_OK);

	hr = D3DXCreateSprite(device, &sprite);
	assert(hr == S_OK);
}

void PrintText::AddText(wstring value)
{
	data += value + L"\n";
}

void PrintText::Render(RECT &rcText, COLORREF color)
{
  	if (data.size() > 0)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		font->DrawTextW(
			sprite, 
			data.c_str(), 
			-1, 
			&rcText,
			DT_NOCLIP, 
			D3DCOLOR(0xFF000000 | color)
		);

		sprite->End();

		data = L"";
	}
}

