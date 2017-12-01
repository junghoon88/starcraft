#include "stdafx.h"
#include "Texture.h"



Texture::Texture(LPDIRECT3DDEVICE9 device, const TCHAR* fileName)
	: _device(device)
{
	TCHAR		szPath[128] = L"";

	wsprintf(szPath, fileName);
	HRESULT hr;
	hr = D3DXCreateTextureFromFileEx
	(
		device
		, szPath
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, 0x0000001
		, 0x0000001
		, 0x00FFFFFF //colorKey
		, &_imageInfo
		, NULL
		, &_texture
	);
	assert(SUCCEEDED(hr));
}


Texture::~Texture()
{
}

void Texture::init(void)
{
	_imgMaxFrameX = 0;
	_imgMaxFrameY = 0;
	_imgFrameWidth = _imageInfo.Width;
	_imgFrameHeight = _imageInfo.Height;
}

void Texture::init(int frameX, int frameY)
{
	if (frameX < 0 || frameY < 0)
	{
		assert(L"Texture frame 값이 음수입니다.");
	}

	_imgMaxFrameX = frameX - 1;
	_imgMaxFrameY = frameY - 1;
	_imgFrameWidth = _imageInfo.Width / frameX;
	_imgFrameHeight = _imageInfo.Height / frameY;
}

void Texture::release(void)
{
	SAFE_RELEASE(_texture);
}


RECT Texture::getRect(void)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = _imageInfo.Width;
	rc.bottom = _imageInfo.Height;
	
	return rc;
}

RECT Texture::getRect(int frameX, int frameY)
{
	if (frameX > _imgMaxFrameX)
		frameX = _imgMaxFrameX;
	if (frameX < 0) 
		frameX = 0;

	if (frameY > _imgMaxFrameY)
		frameY = _imgMaxFrameY;
	if (frameY < 0) 
		frameY = 0;

	RECT rc;
	rc.left   = _imgFrameWidth * frameX;
	rc.top    = _imgFrameHeight * frameY;
	rc.right  = rc.left + _imgFrameWidth;
	rc.bottom = rc.top  + _imgFrameHeight;

	return rc;
}
