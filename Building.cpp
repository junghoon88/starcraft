#include "stdafx.h"
#include "Building.h"
#include "Unit.h"

Building::Building()
{
}


Building::~Building()
{
}

HRESULT Building::init(POINT ptTile)
{
	return S_OK;
}

HRESULT Building::init(POINT ptTile, UINT larvaNum)
{
	return S_OK;
}

void Building::release(void)
{
}

void Building::update(void)
{
	updatePosition();
	updateImageFrame();
}

void Building::render(int imgOffsetX, int imgOffsetY)
{
	if (_battleStatus.clicked)
	{
		RECT temp = _battleStatus.rcEllipse;
		temp.left -= MAINCAMERA->getCameraX();
		temp.right -= MAINCAMERA->getCameraX();
		temp.top -= MAINCAMERA->getCameraY();
		temp.bottom -= MAINCAMERA->getCameraY();

		RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, temp, PENVERSION_UNITCLICK);
	}

	//_baseStatus.imgBody->frameRender(getMemDC(), 
	//	_battleStatus.ptTile.x * TILESIZE - MAINCAMERA->getCameraX(), 
	//	_battleStatus.ptTile.y * TILESIZE - MAINCAMERA->getCameraY(), 
	//	_battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);

	RENDERMANAGER->insertImgFrame(ZORDER_GAMEOBJECT, _baseStatus.imgBody, 
		_battleStatus.ptTile.x * TILESIZE - MAINCAMERA->getCameraX() + imgOffsetX,
		_battleStatus.ptTile.y * TILESIZE - MAINCAMERA->getCameraY() + imgOffsetY,
		_battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);

	//debug
	RENDERMANAGER->insertLineRectangle(ZORDER_INTERFACE2, _battleStatus.rcBody, PENVERSION_BLUE1);
}

void Building::updateBattleStatus(void)
{

}
void Building::updatePosition(void)
{

}
void Building::updateImageFrame(void)
{

}

void Building::procCommands(void)
{

}
