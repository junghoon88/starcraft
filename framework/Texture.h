#pragma once
class Texture
{
private:
	LPDIRECT3DDEVICE9	_device;
	LPDIRECT3DTEXTURE9	_texture;
	D3DXIMAGE_INFO		_imageInfo;

	int _imgMaxFrameX;
	int _imgMaxFrameY;
	int _imgFrameWidth;
	int _imgFrameHeight;


public:
	Texture(LPDIRECT3DDEVICE9 device, const TCHAR* fileName);
	~Texture();

	void init(void);
	void init(int frameX, int frameY);
	void release(void);

	RECT getRect(void);
	RECT getRect(int frameX, int frameY);

	//getter, setter
	inline int getWidth(void) { return _imageInfo.Width; }
	inline int getHeight(void) { return _imageInfo.Height; }
	inline int getFrameWidth(void) { return _imgFrameWidth; }
	inline int getFrameHeight(void) { return _imgFrameHeight; }

	inline int getMaxFrameX(void) { return _imgMaxFrameX; }
	inline int getMaxFrameY(void) { return _imgMaxFrameY; }

	LPDIRECT3DTEXTURE9 getTexture() { return _texture; }
};

