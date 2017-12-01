#include "stdafx.h"
#include "textManager.h"
#include "PrintText.h"

textManager::textManager()
{
}


textManager::~textManager()
{
}

void textManager::init(LPDIRECT3DDEVICE9 device, wstring strKey)
{
	miText iter = _mText.begin();
	iter = _mText.find(strKey);

	//못찾았으면 새로 만든다.
	if (iter == _mText.end())
	{
		PrintText* text;
		text = new PrintText(device);

		_mText.insert(pair<wstring, PrintText*>(strKey, text));
	}
}

void textManager::release(void)
{
	miText iter = _mText.begin();
	for (; iter != _mText.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mText.erase(iter);
		}
		else ++iter;
	}
}

void textManager::addText(wstring strKey, wstring strText)
{
	miText iter = _mText.begin();
	iter = _mText.find(strKey);
	
	if (iter != _mText.end())
	{
		iter->second->AddText(strText);
	}
}

void textManager::setFont(wstring strKey, int height, LPCWSTR fontName)
{
	miText iter = _mText.begin();
	iter = _mText.find(strKey);

	if (iter != _mText.end())
	{
		iter->second->SetFont(height, fontName);
	}
}

void textManager::render(wstring strKey, RECT &rcText, COLORREF color)
{
	miText iter = _mText.begin();
	iter = _mText.find(strKey);

	if (iter != _mText.end())
	{
		iter->second->Render(rcText, color);
	}
}
