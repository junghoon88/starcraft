#pragma once
#include "singletonBase.h"
#include "Sprite.h"
#include "Texture.h"
#include <map>

class textureManager : public singletonBase<textureManager>
{
private:
	typedef map<wstring, Texture*> mapTextureList;
	typedef map<wstring, Texture*>::iterator mapTextureIter;

private:
	mapTextureList	_mTextureList;	//고유 이미지

public:
	textureManager();
	~textureManager();

	void init();
	void release();

	Texture* addTexture(LPDIRECT3DDEVICE9 device, wstring strKey, const TCHAR* fileName);
	Texture* addTexture(LPDIRECT3DDEVICE9 device, wstring strKey, const TCHAR* fileName, int frameX, int frameY);
	Texture* findTexture(wstring strKey);

	void deleteAll(void);

#if 0
	void setCoord(wstring strKey, float destX, float destY);
	void setScale(wstring strKey, float scaleX, float scaleY);
	void setCenterPer(wstring strKey, float centerPerX, float centerPerY); //size 기준 배율로
	void setCenterPos(wstring strKey, float centerPosX, float centerPosY); //position
	void setRotate(wstring strKey, float angleDeg);
	void move(wstring strKey, float moveX, float moveY);
	void setScaleOffset(wstring strKey, float scaleOffsetX, float scaleOffsetY);

	void render(wstring strKey);
	//void render(wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(wstring strKey, int frameX, int frameY);
	//void frameRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//void loopRender(wstring strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	//void alphaRender(wstring strKey, HDC hdc, BYTE alpha);
	//void alphaRender(wstring strKey, HDC hdc, int destX, int destY, BYTE alpha);
	//void alphaRender(wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//void alphaFrameRender(wstring strKey, HDC hdc, int destX, int destY, BYTE alpha);
	//void alphaFrameRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void aniRender(wstring strKey, animation* ani);
	//void aniAlphaRender(wstring strKey, HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	int getCurFrameX(wstring strKey);
	int getCurFrameY(wstring strKey);
	void setCurFrameX(wstring strKey, int frameX);
	void setCurFrameY(wstring strKey, int frameY);
	void setCurFrame(wstring strKey, int frameX, int frameY);
	int getMaxFrameX(wstring strKey);
	int getMaxFrameY(wstring strKey);

	//getter
	wstring FindKeyByImage(Sprite* img);
#endif

};

