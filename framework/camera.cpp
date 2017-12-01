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
	//_cameraX = 0;
	//_cameraY = 0;

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


	if (_targetX < _minX)	_targetX = _minX;
	if (_targetX > _maxX)	_targetX = _maxX;

	if (_targetY < _minY)	_targetY = _minY;
	if (_targetY > _maxY)	_targetY = _maxY;

	if (_targetX != _mainCamera.x)
	{
		int speed = (abs(_targetX - _mainCamera.x)*0.2 + 1) > CAMERA_SPEED ? CAMERA_SPEED : (abs(_targetX - _mainCamera.x)*0.2 + 1);

		if (_targetX > _mainCamera.x)	_mainCamera.x += speed;
		if (_targetX < _mainCamera.x)	_mainCamera.x -= speed;
	}
	if (_targetY != _mainCamera.y)
	{
		int speed = (abs(_targetY - _mainCamera.y)*0.2 + 1) > CAMERA_SPEED ? CAMERA_SPEED : (abs(_targetY - _mainCamera.y)*0.2 + 1);

		if (_targetY > _mainCamera.y)	_mainCamera.y += speed;
		if (_targetY < _mainCamera.y)	_mainCamera.y -= speed;
	}
}


void camera::moveCamera(DIRECTION dir)
{
	switch (dir)
	{
	case DIRECTION_LF:
		_mainCamera.x -= CAMERA_SPEED;
		break;
	case DIRECTION_RG:
		_mainCamera.x += CAMERA_SPEED;
		break;
	case DIRECTION_UP:
		_mainCamera.y -= CAMERA_SPEED;
		break;
	case DIRECTION_DN:
		_mainCamera.y += CAMERA_SPEED;
		break;
	}

	if (_mainCamera.x < _minX)	_mainCamera.x = _minX;
	if (_mainCamera.x > _maxX)	_mainCamera.x = _maxX;

	if (_mainCamera.y < _minY)	_mainCamera.y = _minY;
	if (_mainCamera.y > _maxY)	_mainCamera.y = _maxY;
}


void camera::earthquake(float power)
{
	_mainCamera.x += RND->getFromFloatTo(-power, power);
	_mainCamera.y += RND->getFromFloatTo(-power, power);
}