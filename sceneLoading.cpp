#include "stdafx.h"

#include "sceneLoading.h"


sceneLoading::sceneLoading()
{
}


sceneLoading::~sceneLoading()
{
}

HRESULT sceneLoading::init(void)
{
	_loading = new loading;
	_loading->init();

	TCHAR image[256];

	for (int i = 0; i < 1000; i++)
	{
		memset(&image, 0, sizeof(image));
		_stprintf(image, L"·ÑÇù°î%d", i);
		_loading->loadImage(image, L"·ÑÇù°î.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}


	return S_OK;
}

void sceneLoading::release(void)
{
	SAFE_DELETE(_loading);
}

void sceneLoading::update(void)
{
	_loading->update();

	if (_loading->loadingImageDone())
	{
		SCENEMANAGER->changeScene(L"Çù°î¾À");
	}
}

void sceneLoading::render(void)
{
	_loading->render();
}
