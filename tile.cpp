#include "stdafx.h"
#include "tile.h"
#include "tileNode.h"


tile::tile()
	: _idX(0), _idY(0), 
	_totalCost(0), _costFromStart(0), _costToGoal(0),
	_parentNode(NULL)
{
}


tile::~tile()
{
}

HRESULT tile::init(int idX, int idY)
{
	_center.x = (LONG)((float)(idX + 0.5f) * TILESIZE);
	_center.y = (LONG)((float)(idY + 0.5f) * TILESIZE);

	_idX = idX;
	_idY = idY;

	_rc = RectMakeCenter(_center.x, _center.y, TILESIZE, TILESIZE);

	return S_OK;
}

HRESULT tile::init(int idX, int idY, RECT rc)
{
	_idX = idX;
	_idY = idY;
	_rc = rc;
	_center = { (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 };

	return S_OK;
}

void tile::release(void)
{

}

void tile::update()
{

}

void tile::render()
{
	//FillRect(getMemDC(), &_rc, );
	RectangleMake(getMemDC(), _rc.left, _rc.top, TILESIZE, TILESIZE);
}
