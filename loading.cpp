#include "stdafx.h"
#include "loading.h"

loadItem::loadItem()
{
	ZeroMemory(&_imageResource, sizeof(tagImageResource));
	ZeroMemory(&_soundResource, sizeof(tagSoundResource));
}
loadItem::~loadItem(){}

HRESULT loadItem::initForImage(const TCHAR* keyName, int width, int height, bool blend)
{
	_kind = LOAD_KIND_IMAGE_0;

	_tcscpy(_imageResource.keyName, keyName);
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForImage(const TCHAR* keyName, const TCHAR* fileName, int width, int height, BOOL trans, COLORREF transColor, bool blend)
{
	_kind = LOAD_KIND_IMAGE_1;

	_tcscpy(_imageResource.keyName, keyName);
	_tcscpy(_imageResource.fileName, fileName);
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForImage(const TCHAR* keyName, const TCHAR* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor, bool blend)
{
	_kind = LOAD_KIND_IMAGE_2;

	_tcscpy(_imageResource.keyName, keyName);
	_tcscpy(_imageResource.fileName, fileName);
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(const TCHAR* keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool blend)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	_tcscpy(_imageResource.keyName, keyName);
	_tcscpy(_imageResource.fileName, fileName);
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(const TCHAR* keyName, const TCHAR* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor, bool blend)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	_tcscpy(_imageResource.keyName, keyName);
	_tcscpy(_imageResource.fileName, fileName);
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;
	_imageResource.blend = blend;

	return S_OK;
}

HRESULT loadItem::initForSound(const TCHAR* keyName, const TCHAR* fileName, bool bgm, bool loop)
{
	_kind = LOAD_KIND_SOUND;

	_tcscpy(_soundResource.keyName, keyName);
	_tcscpy(_soundResource.fileName, fileName);
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}


loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	_background = IMAGEMANAGER->addImage(L"로딩백그라운드", L"image/loading/loadingBG.bmp", 640, 400);

	_loadingBar = new progressBar;
	_loadingBar->init(L"progressbarT", L"progressbarB", WINSIZEX / 2, WINSIZEY - 70, 500, 30);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update() 
{
	_loadingBar->update();
}

void loading::render() 
{
	if(_background)	_background->render(getMemDC(), 0, 0);
	_loadingBar->render();

	SetBkMode(getMemDC(), TRANSPARENT);

	if (_currentGauge > 0 && _currentGauge < _vLoadItem.size())
	{
		if (_vLoadItem[_currentGauge]->getLoadingKind() <= LOAD_KIND_FRAMEIMAGE_1)
		{
			int x = _loadingBar->getRect().left;
			int y = _loadingBar->getRect().top - 10;
			TCHAR* name = _vLoadItem[_currentGauge-1]->getImageResource().fileName;
			TextOut(getMemDC(), x, y, name, _tcslen(name));
		}
		else if (_vLoadItem[_currentGauge-1]->getLoadingKind() == LOAD_KIND_SOUND)
		{
			int x = _loadingBar->getRect().left;
			int y = _loadingBar->getRect().top - 10;
			TCHAR* name = _vLoadItem[_currentGauge-1]->getSoundResource().fileName;
			TextOut(getMemDC(), x, y, name, _tcslen(name));
		}
	}

}


void loading::loadImage(const TCHAR* keyName, int width, int height, bool blend)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height, blend);

	_vLoadItem.push_back(item);
}

void loading::loadImage(const TCHAR* keyName, const TCHAR* fileName, int width, int height, BOOL trans, COLORREF transColor, bool blend)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor, blend);

	_vLoadItem.push_back(item);
}

void loading::loadImage(const TCHAR* keyName, const TCHAR* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor, bool blend)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor, blend);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(const TCHAR* keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool blend)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor, blend);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(const TCHAR* keyName, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool blend)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor, blend);

	_vLoadItem.push_back(item);
}

void loading::loadSound(const TCHAR* keyName, const TCHAR* fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, fileName, bgm, loop);

	_vLoadItem.push_back(item);
}


BOOL loading::loadingImageDone()
{
	//로딩이 끝났으면 다됐다고 전해라~
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height, img.blend);
		}
		break;
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor, img.blend);
		}
		break;
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor, img.blend);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor, img.blend);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor, img.blend);
		}
		break;
		case LOAD_KIND_SOUND:
		{
			tagSoundResource sound = item->getSoundResource();
			SOUNDMANAGER->addSound(sound.keyName, sound.fileName, sound.bgm, sound.loop);
		}
		break;
	}

	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	_currentGauge++;

	return FALSE;
}
