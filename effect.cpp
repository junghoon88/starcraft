#include "stdafx.h"
#include "effect.h"
#include "animation.h"

effect::effect()
	: _effectImage(NULL), 
	_effectAnimation(NULL),
	_isRunning(false), 
	_x(0), _y(0), _zorder(ZORDER_TILES)
{
}


effect::~effect()
{

}

HRESULT effect::init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;

	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();


	return S_OK;
}

HRESULT effect::init(image* effectImage, int fps, float elapsedTime)
{
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;

	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), _effectImage->getFrameWidth(), _effectImage->getFrameHeight());
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();


	return S_OK;
}

void effect::release(void)
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::update(void)
{
	if (!_isRunning) return;

	_effectAnimation->frameUpdate(_elapsedTime);

	if (!_effectAnimation->isPlay()) killEffect();
}

void effect::render(void)
{
	if (!_isRunning) return;

	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

void effect::render(ZORDER zorder)
{
	if (!_isRunning) return;

	RENDERMANAGER->insertImgAni(zorder, _effectImage, _x, _y, _effectAnimation);
}

void effect::Zrender(void)
{
	if (!_isRunning) return;

	RENDERMANAGER->insertImgAni(_zorder, _effectImage, _x - MAINCAMERA->getCameraX(), _y - MAINCAMERA->getCameraY(), _effectAnimation);
}


void effect::startEffect(int x, int y)
{
	if (!_effectImage || !_effectAnimation) return;

	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}

void effect::startEffect(POINT pt)
{
	if (!_effectImage || !_effectAnimation) return;

	_x = pt.x - (_effectAnimation->getFrameWidth() / 2);
	_y = pt.y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}


void effect::killEffect(void)
{
	_isRunning = false;
}
