#include "stdafx.h"
#include "gameInterface.h"


gameInterface::gameInterface()
	: _imgInterface(NULL)
{
}


gameInterface::~gameInterface()
{
}

HRESULT gameInterface::init(RACES race)
{
	switch (race)
	{
	case RACES_TERRAN:
		_imgInterface = IMAGEMANAGER->findImage(L"interfaceT");
		break;
	case RACES_PROTOSS:
		_imgInterface = IMAGEMANAGER->findImage(L"interfaceP");
		break;
	case RACES_ZERG:
		_imgInterface = IMAGEMANAGER->findImage(L"interfaceZ");
		break;
	}

	return S_OK;
}

void gameInterface::release(void)
{
}

void gameInterface::update(void) 
{
	//인터페이스 영역 밖에 마우스가 있을경우
	if (GetPixel(_imgInterface->getMemDC(), _ptMouse.x, _ptMouse.y) & 0x00FFFFFF == RGB(255, 0, 255)) return;


}

void gameInterface::render(void) 
{
	if (_imgInterface == NULL)
		return;

	_imgInterface->render(getMemDC());
}

