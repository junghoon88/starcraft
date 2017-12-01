#include "stdafx.h"
#include "keyAniManager.h"
#include "Sprite.h"
#include "Texture.h"
#include "animation.h"

keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{

}

HRESULT keyAniManager::init()
{

	return S_OK;
}

void keyAniManager::release()
{
	deleteAll();
}

void keyAniManager::update() 
{
	for (int i = 0; i < _vTotalAnimation.size(); i++)
	{
		iterAnimations iter = _vTotalAnimation[i].begin();
		
		for (iter; iter != _vTotalAnimation[i].end(); ++iter)
		{
			//애니메이션이 재생중이지 않으면 재생하지 않는다
			if (!iter->second->isPlay()) continue;

			iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
		}
	}
}

void keyAniManager::render() 
{

}


//디폴트 키 애니메이션
void keyAniManager::addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop)							  
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	arrAnimation arrAni; 
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction)			  
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNC)cbFunction);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);

}

void keyAniManager::addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNC_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);

}


//배열 키 애니메이션
void keyAniManager::addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop)								
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);


	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction)			
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNC)cbFunction);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj)
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNC_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}


//구간 키 애니메이션
void keyAniManager::addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop)							   
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction)		   
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNC)cbFunction);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	Sprite* sprite = IMAGEMANAGER->findSprite(imageKeyName);
	Texture* texture = sprite->getTexture();
	animation* ani = new animation;

	ani->init(texture->getWidth(), texture->getHeight(), texture->getFrameWidth(), texture->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNC_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}


void keyAniManager::start(wstring animationKeyName) 
{
	for (int i = 0; i < _vTotalAnimation.size(); i++)
	{
		iterAnimations iter = _vTotalAnimation[i].find(animationKeyName);
		iter->second->start();
	}
}

void keyAniManager::stop(wstring animationKeyName)  
{
	for (int i = 0; i < _vTotalAnimation.size(); i++)
	{
		iterAnimations iter = _vTotalAnimation[i].find(animationKeyName);
		iter->second->stop();
	}
}

void keyAniManager::pause(wstring animationKeyName) 
{
	for (int i = 0; i < _vTotalAnimation.size(); i++)
	{
		iterAnimations iter = _vTotalAnimation[i].find(animationKeyName);
		iter->second->pause();
	}
}

void keyAniManager::resume(wstring animationKeyName)
{
	for (int i = 0; i < _vTotalAnimation.size(); i++)
	{
		iterAnimations iter = _vTotalAnimation[i].find(animationKeyName);
		iter->second->resume();
	}
}


animation* keyAniManager::findAnimation(wstring animationKeyName)
{
	for (int i = 0; i < _vTotalAnimation.size(); i++)
	{
		iterAnimations iter = _vTotalAnimation[i].find(animationKeyName);

		if (iter != _vTotalAnimation[i].end())
		{
			return iter->second;
		}
	}

	return NULL;
}



void keyAniManager::deleteAll()
{
	viArrAnimation viter = _vTotalAnimation.begin();
	for (viter; viter != _vTotalAnimation.end(); ++viter)
	{
		for (iterAnimations iter = (*viter).begin(); iter != (*viter).end();)
		{
			if (iter->second != NULL)
			{
				iter->second->release();
				SAFE_DELETE(iter->second);
				iter = (*viter).erase(iter);
			}
			else ++iter;
		}
		(*viter).clear();
	}
	_vTotalAnimation.clear();
}
