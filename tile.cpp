#include "stdafx.h"
#include "tile.h"
#include "tileNode.h"


tile::tile()
	: _idX(0), _idY(0), 
	_totalCost(0)
{
}


tile::~tile()
{
}

HRESULT tile::init(int idX, int idY)
{
	_center = PointMake(idX * TILESIZE + (TILESIZE / 2), idY*TILESIZE + (TILESIZE / 2));

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
	_center = PointMake((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2);

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

}
