#include "stdafx.h"
#include "camera.h"
#include "tileNode.h"

camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init(void)
{
	_cameraX = 0;
	_cameraY = 0;

	_minX = 0;
	_minY = 0;
	_maxX = MAP_WIDTH - WINSIZEX;
	_maxY = MAP_HEIGHT - WINSIZEY;


	return S_OK;
}
void camera::release(void)
{

}
void camera::update(void) 
{
	_rcCamera = RectMake(_cameraX, _cameraY, WINSIZEX, WINSIZEY);
}

void camera::render(HDC hdc)
{
	TCHAR str[256];
	SetBkMode(hdc, TRANSPARENT);

	wsprintf(str, L"camera : <%d, %d>", _cameraX, _cameraY);
	TextOut(hdc, 0, 60, str, _tcslen(str));
}


void camera::moveCamera(DIRECTION dir)
{
	switch (dir)
	{
	case DIRECTION_LF:
		_cameraX -= CAMERA_SPEED;
		break;
	case DIRECTION_RG:
		_cameraX += CAMERA_SPEED;
		break;
	case DIRECTION_UP:
		_cameraY -= CAMERA_SPEED;
		break;
	case DIRECTION_DN:
		_cameraY += CAMERA_SPEED;
		break;

	case DIRECTION_RU:
		_cameraX += CAMERA_SPEED;
		_cameraY -= CAMERA_SPEED;
		break;
	case DIRECTION_LU:
		_cameraX -= CAMERA_SPEED;
		_cameraY -= CAMERA_SPEED;
		break;
	case DIRECTION_LD:
		_cameraX -= CAMERA_SPEED;
		_cameraY += CAMERA_SPEED;
		break;
	case DIRECTION_RD:
		_cameraX += CAMERA_SPEED;
		_cameraY += CAMERA_SPEED;
		break;

	}

	if (_cameraX < _minX)	_cameraX = _minX;
	if (_cameraX > _maxX)	_cameraX = _maxX;

	if (_cameraY < _minY)	_cameraY = _minY;
	if (_cameraY > _maxY)	_cameraY = _maxY;
}


void camera::earthquake(float power)
{
	_cameraX += RND->getFromFloatTo(-power, power);
	_cameraY += RND->getFromFloatTo(-power, power);
}


bool camera::moveable(DIRECTION dir)
{
	switch (dir)
	{
	case DIRECTION_LF:		if (_cameraX <= _minX)							return FALSE;		break;
	case DIRECTION_RG:		if (_cameraX >= _maxX)							return FALSE;		break;
	case DIRECTION_UP:		if (_cameraY <= _minY)							return FALSE;		break;
	case DIRECTION_DN:		if (_cameraY >= _maxY)							return FALSE;		break;
	case DIRECTION_RU:		if (_cameraX >= _maxX && _cameraY <= _minY)		return FALSE;		break;
	case DIRECTION_LU:		if (_cameraX <= _minX && _cameraY <= _minY)		return FALSE;		break;
	case DIRECTION_LD:		if (_cameraX <= _minX && _cameraY >= _maxY)		return FALSE;		break;
	case DIRECTION_RD:		if (_cameraX >= _maxX && _cameraY >= _maxY)		return FALSE;		break;
	}

	return TRUE;
}


void camera::setCameraX(int x)
{
	_cameraX = x;

	if (_cameraX < _minX)	_cameraX = _minX;
	if (_cameraX > _maxX)	_cameraX = _maxX;
}
void camera::setCameraY(int y)
{
	_cameraY = y; 

	if (_cameraY < _minY)	_cameraY = _minY;
	if (_cameraY > _maxY)	_cameraY = _maxY;
}
