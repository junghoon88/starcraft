#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(TCHAR* name)
{
	TCHAR str[100] = L"";
	_stprintf_s(str, L"frontBar%s", name);
	_progressBarTop = IMAGEMANAGER->findImage(str);
	_stprintf_s(str, L"backBar%s", name);
	_progressBarBottom = IMAGEMANAGER->findImage(str);

	_gaugeWidth = 0.0f;

	_imgWidth = _progressBarBottom->getWidth();
	_imgHeight = _progressBarBottom->getHeight();

	_rcProgress = RectMake(0, 0, _imgWidth, _imgHeight);

	return S_OK;
}
HRESULT progressBar::init(TCHAR* topImage, TCHAR* bottomImage)
{
	_progressBarTop = IMAGEMANAGER->findImage(topImage);
	_progressBarBottom = IMAGEMANAGER->findImage(bottomImage);

	_gaugeWidth = 0.0f;

	_imgWidth = _progressBarBottom->getWidth();
	_imgHeight = _progressBarBottom->getHeight();

	_rcProgress = RectMake(0, 0, _imgWidth, _imgHeight);

	return S_OK;
}


void progressBar::release(void)
{

}

void progressBar::update(void)
{

}

void progressBar::render(void)
{
	if (_progressBarBottom)
	{
		_progressBarBottom->render(getMemDC(), _rcProgress.left, _rcProgress.top, 0, 0,
			(int)_progressBarBottom->getWidth(),
			(int)_progressBarBottom->getHeight());
	}

	if (_progressBarTop)
	{
		_progressBarTop->render(getMemDC(), _rcProgress.left, _rcProgress.top, 0, 0,
			(int)_gaugeWidth,
			(int)_progressBarTop->getHeight());
	}
}

void progressBar::ZRender(ZORDER zorder)
{
	if (_progressBarBottom)
	{
		RENDERMANAGER->insertImg(zorder, _progressBarBottom, _rcProgress.left, _rcProgress.top);
	}

	if (_progressBarTop)
	{
		RENDERMANAGER->insertImg(zorder, _progressBarTop, _rcProgress.left, _rcProgress.top, (int)_gaugeWidth, (int)_progressBarTop->getHeight());
	}
}


void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_gaugeWidth = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}
