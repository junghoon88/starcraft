#include "stdafx.h"
#include "camera.h"

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

	_targetX = 0;
	_targetY = 0;


	return S_OK;
}
void camera::release(void)
{

}
void camera::update(void) 
{


	//if (_targetX < _minX)	_targetX = _minX;
	//if (_targetX > _maxX)	_targetX = _maxX;
	//
	//if (_targetY < _minY)	_targetY = _minY;
	//if (_targetY > _maxY)	_targetY = _maxY;
	//
	//if (_targetX != _cameraX)
	//{
	//	int speed = (abs(_targetX - _cameraX)*0.2 + 1) > CAMERA_SPEED ? CAMERA_SPEED : (abs(_targetX - _cameraX)*0.2 + 1);
	//
	//	if (_targetX > _cameraX)	_cameraX += speed;
	//	if (_targetX < _cameraX)	_cameraX -= speed;
	//}
	//if (_targetY != _cameraY)
	//{
	//	int speed = (abs(_targetY - _cameraY)*0.2 + 1) > CAMERA_SPEED ? CAMERA_SPEED : (abs(_targetY - _cameraY)*0.2 + 1);
	//
	//	if (_targetY > _cameraY)	_cameraY += speed;
	//	if (_targetY < _cameraY)	_cameraY -= speed;
	//}


	//if (_cameraX < WINSIZEX / 2)				_cameraX = WINSIZEX / 2;
	//if (_cameraX > MAP_WIDTH - WINSIZEX / 2)	_cameraX = MAP_WIDTH - WINSIZEX / 2;
	//if (_cameraY < WINSIZEY / 2)				_cameraY = WINSIZEY / 2;
	//if (_cameraY > MAP_WIDTH - WINSIZEY / 2)	_cameraY = MAP_WIDTH - WINSIZEY / 2;

	//if (_cameraX < 0)						_cameraX = 0;
	//if (_cameraX > MAP_WIDTH - WINSIZEX)	_cameraX = MAP_WIDTH - WINSIZEX;
	//if (_cameraY < MAP_SKY)								_cameraY = MAP_SKY;
	//if (_cameraY > MAP_SKY + MAP_HEIGHT - WINSIZEY)		_cameraY = MAP_SKY + MAP_HEIGHT - WINSIZEY;

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