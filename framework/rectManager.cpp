#include "stdafx.h"
#include "rectManager.h"

rectManager::rectManager()
{
}


rectManager::~rectManager()
{
}

void rectManager::init(void)
{

}

void rectManager::release(void)
{
	deleteAll();
}

Rect* rectManager::addRect(LPDIRECT3DDEVICE9 device, wstring strKey, D3DXVECTOR2 coord, D3DXVECTOR2 size, COLORREF color, BYTE alpha)
{
	DWORD colorARGB = color | (alpha << 24);
	Rect* rc = new Rect(device, coord, size, colorARGB);
	rc->init();

	_mRectList.insert(pair<wstring, Rect*>(strKey, rc));

	return rc;
}

BOOL rectManager::deleteAll(void)
{
	mRectiter iter = _mRectList.begin();
	for (; iter != _mRectList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_RELEASE2(iter->second);
			iter = _mRectList.erase(iter);
		}
		else ++iter;
	}
	
	_mRectList.clear();
	
	return TRUE;
}

Rect* rectManager::findRect(wstring strKey)
{
	mRectiter iter = _mRectList.find(strKey);

	if (iter != _mRectList.end())
	{
		return iter->second;
	}

	return NULL;
}


void rectManager::render(wstring strKey, bool cameraOffset)
{
	Rect* rc = findRect(strKey);

	if (rc) rc->render(cameraOffset);
}

RECT rectManager::getRect(wstring strKey)
{
	Rect* rc = findRect(strKey);

	if (rc) return rc->getRect();

	return { 0,0,0,0 };
}

void rectManager::setCoord(wstring strKey, float x, float y)
{
	Rect* rc = findRect(strKey);

	if (rc) rc->setCoord({ x, y });
}

void rectManager::setSize(wstring strKey, float x, float y)
{
	Rect* rc = findRect(strKey);

	if (rc) rc->setSize({ x, y });
}

void rectManager::setScale(wstring strKey, float x, float y)
{
	Rect* rc = findRect(strKey);

	D3DXVECTOR2 scale = { x, y };
	if (rc) rc->setScale(&scale);
}

void rectManager::setRotate(wstring strKey, float angleDeg)
{
	Rect* rc = findRect(strKey);

	if (rc) rc->setRotate(angleDeg);

}

void rectManager::setCenterPer(wstring strKey, float x, float y)
{
	Rect* rc = findRect(strKey);

	if (rc) rc->setCenterPer({ x, y });

}

void rectManager::setCenterPos(wstring strKey, float x, float y)
{
	Rect* rc = findRect(strKey);

	if (rc) rc->setCenterPos({ x, y });
}

void rectManager::setColor(wstring strKey, COLORREF color, BYTE alpha)
{
	Rect* rc = findRect(strKey);
	DWORD colorARGB = color | (alpha << 24);
	
	if (rc) rc->setColor(colorARGB);
}

void rectManager::move(wstring strKey, float moveX, float moveY)
{
	Rect* rc = findRect(strKey);

	if (rc) rc->move(moveX, moveY);
}
