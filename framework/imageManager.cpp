#include "stdafx.h"
#include "imageManager.h"



imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

void imageManager::init()
{

}
void imageManager::release()
{
	deleteAll();
}

Texture* imageManager::addTexture(LPDIRECT3DDEVICE9 device, wstring strKey, const TCHAR* fileName)
{
	Texture* texture = findTexture(strKey);

	if (texture) return texture;

	texture = new Texture(device, fileName);
	texture->init();

	_mTextureList.insert(make_pair(strKey, texture));

	return texture;
}

Texture* imageManager::addTexture(LPDIRECT3DDEVICE9 device, wstring strKey, const TCHAR* fileName, int frameX, int frameY)
{
	Texture* texture = findTexture(strKey);

	if (texture) return texture;

	texture = new Texture(device, fileName);
	texture->init(frameX, frameY);

	_mTextureList.insert(make_pair(strKey, texture));

	return texture;
}

Texture* imageManager::findTexture(wstring strKey)
{
	mapTextureIter key = _mTextureList.find(strKey);

	if (key != _mTextureList.end())
	{
		return key->second;
	}

	return NULL;
}

Sprite* imageManager::addSprite(LPDIRECT3DDEVICE9 device, wstring strKey, wstring strTextureKey, bool bCameraOffset)
{
	Sprite* sprite = findSprite(strKey);
	Texture* texture = findTexture(strTextureKey);

	if (sprite) return sprite;

	sprite = new Sprite(device);
	sprite->init(texture, bCameraOffset);

	_mSpriteList.insert(make_pair(strKey, sprite));

	return sprite;
}

Sprite* imageManager::findSprite(wstring strKey)
{
	mapSpriteIter key = _mSpriteList.find(strKey);

	if (key != _mSpriteList.end())
	{
		return key->second;
	}

	return NULL;
}

void imageManager::deleteAll(void)
{
	mapSpriteIter sIter = _mSpriteList.begin();
	while(sIter != _mSpriteList.end())
	{
		if ((*sIter).second)
		{
			(*sIter).second->release();
			SAFE_DELETE((*sIter).second);
			_mSpriteList.erase(sIter);
		}
		else ++sIter;
	}


	mapTextureIter tIter = _mTextureList.begin();
	while (tIter != _mTextureList.end())
	{
		if ((*tIter).second)
		{
			(*tIter).second->release();
			SAFE_DELETE((*tIter).second);
			_mTextureList.erase(tIter);
		}
		else ++tIter;
	}
}



#if 0
void imageManager::setCoord(wstring strKey, float destX, float destY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setCoord({ destX, destY });
}

void imageManager::setScale(wstring strKey, float scaleX, float scaleY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setScale({ scaleX, scaleY});
}

void imageManager::setCenterPer(wstring strKey, float centerPerX, float centerPerY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setCenterPer({ centerPerX, centerPerY });
}


void imageManager::setCenterPos(wstring strKey, float centerPosX, float centerPosY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setCenterPos({ centerPosX, centerPosY });
}

void imageManager::setRotate(wstring strKey, float angleDeg)				  
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setRotate(angleDeg);
}

void imageManager::move(wstring strKey, float moveX, float moveY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->move(moveX, moveY);
}

void imageManager::setScaleOffset(wstring strKey, float scaleOffsetX, float scaleOffsetY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setScaleOffset(scaleOffsetX, scaleOffsetY);
}





void imageManager::render(wstring strKey)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->render();
}

void imageManager::frameRender(wstring strKey, int frameX, int frameY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->frameRender(frameX, frameY);
}

void imageManager::aniRender(wstring strKey, animation* ani)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) sprite->aniRender(ani);
}


int imageManager::getCurFrameX(wstring strKey)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) return sprite->getCurFrameX();

	return 0;
}
int imageManager::getCurFrameY(wstring strKey)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) return sprite->getCurFrameY();

	return 0;
}

void imageManager::setCurFrameX(wstring strKey, int frameX)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) sprite->setCurFrameX(frameX);
}

void imageManager::setCurFrameY(wstring strKey, int frameY)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) sprite->setCurFrameY(frameY);
}

void imageManager::setCurFrame(wstring strKey, int frameX, int frameY)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) sprite->setCurFrameX(frameX);
	if (sprite) sprite->setCurFrameY(frameY);
}
int imageManager::getMaxFrameX(wstring strKey)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) return sprite->getMaxFrameX();

	return 0;
}

int imageManager::getMaxFrameY(wstring strKey)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) return sprite->getCurFrameY();

	return 0;
}

wstring imageManager::FindKeyByImage(Sprite* img)
{
	mapImageIter iter = _mSpriteList.begin();

	for (iter; iter != _mSpriteList.end(); ++iter)
	{
		if (img == iter->second)
		{
			return iter->first;
		}
	}

	return L"";
}
#endif
