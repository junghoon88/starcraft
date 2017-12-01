#include "stdafx.h"
#include "Rect.h"


Rect::Rect(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 coord, D3DXVECTOR2 size, DWORD color)
	: _device(device), _lineColor(color), _coord(coord), _size(size), _angleDeg(0.0f), _scale(1, 1)
{
	_center.x = _size.x * 0.5f;
	_center.y = _size.y * 0.5f;

	D3DXMatrixIdentity(&_world);
}
Rect::~Rect()
{

}

void Rect::init()
{
	HRESULT hr;
	hr = D3DXCreateLine(_device, &_line);
	assert(SUCCEEDED(hr));

	AdjustTransform();
}
void Rect::release()
{
	SAFE_RELEASE(_line);
}
void Rect::update()
{

}
void Rect::render(bool cameraOffset)
{
	D3DVIEWPORT9 viewport;
	_device->GetViewport(&viewport);

	D3DXVECTOR3 _lineVectorOffset[5];
	for (int i = 0; i < 5; i++)
	{
		if (cameraOffset)
		{
			_lineVectorOffset[i].x = _lineVector[i].x - _mainCamera.x;
			_lineVectorOffset[i].y = _lineVector[i].y - _mainCamera.y;
			_lineVectorOffset[i].z = _lineVector[i].z;
		}
		else
		{
			_lineVectorOffset[i].x = _lineVector[i].x;
			_lineVectorOffset[i].y = _lineVector[i].y;
			_lineVectorOffset[i].z = _lineVector[i].z;
		}
	}

	D3DXMATRIX ortho;
	D3DXMatrixOrthoOffCenterLH(&ortho, 0, viewport.Width, viewport.Height, 0, 0, 1);

	_line->Begin();
	//_line->DrawTransform(_lineVector, 5, &ortho, _lineColor);
	_line->DrawTransform(_lineVectorOffset, 5, &ortho, _lineColor);
	_line->End();
}

void Rect::AdjustTransform()
{
	_lineVector[0] = D3DXVECTOR3(0, 0, 0);
	_lineVector[1] = D3DXVECTOR3(_size.x, 0, 0);
	_lineVector[2] = D3DXVECTOR3(_size.x, _size.y, 0);
	_lineVector[3] = D3DXVECTOR3(0, _size.y, 0);
	_lineVector[4] = D3DXVECTOR3(0, 0, 0);

	D3DXMatrixIdentity(&_world);

	float angle = D3DXToRadian(_angleDeg);
	D3DXMATRIX scale;
	D3DXMATRIX rotation;
	D3DXMATRIX rotationCenter;
	D3DXMATRIX rotationInverseCenter;
	D3DXMATRIX translate;

	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixIdentity(&rotationCenter);
	D3DXMatrixIdentity(&rotationInverseCenter);
	D3DXMatrixIdentity(&translate);


	D3DXMatrixScaling(&scale, _scale.x, _scale.y, 1.0f);

	//D3DXVECTOR2 center;
	//center.x = size.x * 0.5f;
	//center.y = size.y * 0.5f;

	D3DXMatrixTranslation(&rotationInverseCenter, -_center.x, -_center.y, 0);
	{
		D3DXMatrixRotationZ(&rotation, -angle);
	}
	D3DXMatrixTranslation(&rotationCenter, _center.x, _center.y, 0);
	D3DXMatrixTranslation(&translate, FLOAT(_coord.x), FLOAT(_coord.y), 0);

	_world = scale * rotationInverseCenter * rotation *
		rotationCenter * translate;

	for (int i = 0; i < 5; i++)
		D3DXVec3TransformCoord(&_lineVector[i], &_lineVector[i], &_world);
}

//getter, setter
RECT Rect::getRect()
{
	RECT rect =
	{
		_coord.x,
		_coord.y,
		_coord.x + _size.x,
		_coord.y + _size.y
	};

	return rect;
}

void Rect::setCoord(D3DXVECTOR2 coord)
{
	_coord = coord;

	AdjustTransform();
}
void Rect::setSize(D3DXVECTOR2 size)
{
	_size = size;

	AdjustTransform();
}
void Rect::setScale(const D3DXVECTOR2* scale)
{
	if (_scale == *scale)
		return;

	_scale = *scale;
	
	_size.x = _size.x * _scale.x;
	_size.y = _size.y * _scale.y;

	AdjustTransform();
}
void Rect::setRotate(float angleDeg)
{
	_angleDeg = angleDeg;

	AdjustTransform();
}

void Rect::setCenterPer(D3DXVECTOR2 centerPer)
{
	_center.x = _size.x * centerPer.x;
	_center.y = _size.y * centerPer.y;

	AdjustTransform();
}
void Rect::setCenterPos(D3DXVECTOR2 centerPos)
{
	_center.x = centerPos.x;
	_center.y = centerPos.y;

	AdjustTransform();
}


void Rect::move(float moveX, float moveY)
{
	_coord.x += moveX;
	_coord.y += moveY;

	AdjustTransform();
}

