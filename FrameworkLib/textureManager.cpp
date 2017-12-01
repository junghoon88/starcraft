#include "stdafx.h"
#include "textureManager.h"



textureManager::textureManager()
{
}


textureManager::~textureManager()
{
}

void textureManager::init()
{

}
void textureManager::release()
{
	deleteAll();
}

Texture* textureManager::addTexture(LPDIRECT3DDEVICE9 device, wstring strKey, const TCHAR* fileName)
{
	Texture* texture = findTexture(strKey);

	if (texture) return texture;

	texture = new Texture(device, fileName);
	texture->init();

	_mTextureList.insert(make_pair(strKey, texture));

	return texture;
}

Texture* textureManager::addTexture(LPDIRECT3DDEVICE9 device, wstring strKey, const TCHAR* fileName, int frameX, int frameY)
{
	Texture* texture = findTexture(strKey);

	if (texture) return texture;

	texture = new Texture(device, fileName);
	texture->init(frameX, frameY);

	_mTextureList.insert(make_pair(strKey, texture));

	return texture;
}

Texture* textureManager::findTexture(wstring strKey)
{
	mapTextureIter key = _mTextureList.find(strKey);

	if (key != _mTextureList.end())
	{
		return key->second;
	}

	return NULL;
}

void textureManager::deleteAll(void)
{
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
void textureManager::setCoord(wstring strKey, float destX, float destY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setCoord({ destX, destY });
}

void textureManager::setScale(wstring strKey, float scaleX, float scaleY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setScale({ scaleX, scaleY});
}

void textureManager::setCenterPer(wstring strKey, float centerPerX, float centerPerY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setCenterPer({ centerPerX, centerPerY });
}


void textureManager::setCenterPos(wstring strKey, float centerPosX, float centerPosY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setCenterPos({ centerPosX, centerPosY });
}

void textureManager::setRotate(wstring strKey, float angleDeg)				  
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setRotate(angleDeg);
}

void textureManager::move(wstring strKey, float moveX, float moveY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->move(moveX, moveY);
}

void textureManager::setScaleOffset(wstring strKey, float scaleOffsetX, float scaleOffsetY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->setScaleOffset(scaleOffsetX, scaleOffsetY);
}





void textureManager::render(wstring strKey)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->render();
}

void textureManager::frameRender(wstring strKey, int frameX, int frameY)
{
	Sprite* sprite = findImage(strKey);

	if (sprite) sprite->frameRender(frameX, frameY);
}

void textureManager::aniRender(wstring strKey, animation* ani)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) sprite->aniRender(ani);
}


int textureManager::getCurFrameX(wstring strKey)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) return sprite->getCurFrameX();

	return 0;
}
int textureManager::getCurFrameY(wstring strKey)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) return sprite->getCurFrameY();

	return 0;
}

void textureManager::setCurFrameX(wstring strKey, int frameX)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) sprite->setCurFrameX(frameX);
}

void textureManager::setCurFrameY(wstring strKey, int frameY)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) sprite->setCurFrameY(frameY);
}

void textureManager::setCurFrame(wstring strKey, int frameX, int frameY)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) sprite->setCurFrameX(frameX);
	if (sprite) sprite->setCurFrameY(frameY);
}
int textureManager::getMaxFrameX(wstring strKey)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) return sprite->getMaxFrameX();

	return 0;
}

int textureManager::getMaxFrameY(wstring strKey)
{
	Sprite * sprite = findImage(strKey);

	if (sprite) return sprite->getCurFrameY();

	return 0;
}

wstring textureManager::FindKeyByImage(Sprite* img)
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
