#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(TCHAR* name, int x, int y, int width, int height)
{
	_pt.x = x;
	_pt.y = y;

	_rcProgress = RectMake(x, y, width, height);

	TCHAR str[100] = L"";
	_stprintf_s(str, L"frontBar%s", name);
	_progressBarTop = IMAGEMANAGER->addImage(str, L"image/hpBarTop.bmp", (float)x, (float)y, width, height, true, RGB(255, 0, 255));
	_stprintf_s(str, L"backBar%s", name);
	_progressBarBottom = IMAGEMANAGER->addImage(str, L"image/hpBarBottom.bmp", (float)x, (float)y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarTop->getWidth();

	return S_OK;
}

HRESULT progressBar::init(TCHAR* topImage, TCHAR* bottomImage, float x, float y, int width, int height)
{
	_pt.x = (LONG)x;
	_pt.y = (LONG)y;

	_rcProgress = RectMake((int)x, (int)y, width, height);

	TCHAR strTopImageName[128];
	TCHAR strBottomImageName[128];

	ZeroMemory(strTopImageName, sizeof(strTopImageName));
	ZeroMemory(strBottomImageName, sizeof(strBottomImageName));

	_stprintf_s(strTopImageName, L"image/loading/%s.bmp", topImage);
	_stprintf_s(strBottomImageName, L"image/loading/%s.bmp", bottomImage);

	_progressBarBottom = IMAGEMANAGER->addImage(bottomImage, strBottomImageName, (float)x, (float)y, width, height, true, RGB(255, 0, 255));
	_progressBarTop = IMAGEMANAGER->addImage(topImage, strTopImageName, (float)x, (float)y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarTop->getWidth();

	return S_OK;
}
HRESULT progressBar::init(TCHAR* topImage, TCHAR* bottomImage, float x, float y, int width, int height, TCHAR* foldername)
{
	_pt.x = (LONG)x;
	_pt.y = (LONG)y;

	_rcProgress = RectMake((int)x, (int)y, width, height);

	TCHAR strTopImageName[128];
	TCHAR strBottomImageName[128];

	ZeroMemory(strTopImageName, sizeof(strTopImageName));
	ZeroMemory(strBottomImageName, sizeof(strBottomImageName));

	_stprintf_s(strTopImageName, L"image/%s/%s.bmp", foldername, topImage);
	_stprintf_s(strBottomImageName, L"image/%s/%s.bmp", foldername, bottomImage);

	_progressBarBottom = IMAGEMANAGER->addImage(bottomImage, strBottomImageName, (float)x, (float)y, width, height, true, RGB(255, 0, 255));
	_progressBarTop = IMAGEMANAGER->addImage(topImage, strTopImageName, (float)x, (float)y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarTop->getWidth();

	return S_OK;
}

void progressBar::release(void)
{

}

void progressBar::update(void)
{
	_rcProgress = RectMakeCenter(_pt.x, _pt.y, (int)_progressBarBottom->getWidth(), (int)_progressBarBottom->getHeight());
}

void progressBar::render(void)
{
	if (_progressBarBottom)
	{
		_progressBarBottom->render(getMemDC(), _rcProgress.left, _pt.y, 0, 0,
			(int)_progressBarBottom->getWidth(),
			(int)_progressBarBottom->getHeight());
	}

	if (_progressBarTop)
	{
		_progressBarTop->render(getMemDC(), _rcProgress.left, _pt.y, 0, 0,
			(int)_width,
			(int)_progressBarTop->getHeight());
	}
}

void progressBar::render(TCHAR* name)
{
	TCHAR str[100] = L"";
	_stprintf_s(str, L"backBar%s", name);
	IMAGEMANAGER->render(str, getMemDC(), _pt.x, _pt.y + (int)_progressBarBottom->getHeight() / 2,
		0, 0,
		(int)_progressBarBottom->getWidth(), (int)_progressBarBottom->getHeight());

	_stprintf_s(str, L"frontBar%s", name);
	IMAGEMANAGER->render(str, getMemDC(), _pt.x, _pt.y + (int)_progressBarBottom->getHeight() / 2,
		0, 0,
		(int)_width, (int)_progressBarBottom->getHeight());

}


void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}
