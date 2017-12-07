#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
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
			//�ִϸ��̼��� ��������� ������ ������� �ʴ´�
			if (!iter->second->isPlay()) continue;

			iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
		}
	}
}

void keyAniManager::render() 
{

}


//����Ʈ Ű �ִϸ��̼�
void keyAniManager::addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop)							  
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	arrAnimation arrAni; 
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction)			  
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);

}

void keyAniManager::addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);

}


//�迭 Ű �ִϸ��̼�
void keyAniManager::addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop)								
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);


	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction)			
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}


//���� Ű �ִϸ��̼�
void keyAniManager::addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop)							   
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction)		   
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	arrAnimation arrAni;
	arrAni.insert(pair<wstring, animation*>(animationKeyName, ani));
	_vTotalAnimation.push_back(arrAni);
}

void keyAniManager::addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
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
