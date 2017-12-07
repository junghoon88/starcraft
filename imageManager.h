#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>


class imageManager : public singletonBase<imageManager>
{
private:
	//         키 값(first)자료값(second)
	typedef map<wstring, image*> mapImageList;
	typedef map<wstring, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT init();
	void release();

	image* addImage(wstring strKey, int width, int height, bool blend = FALSE);
	image* addImage(wstring strKey, const TCHAR* fileName, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	image* addImage(wstring strKey, const TCHAR* fileName, float x, float y, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);

	image* addFrameImage(wstring strKey, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	image* addFrameImage(wstring strKey, const TCHAR* fileName, int width, int height, int frameX, int frameY, bool trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);

	image* findImage(wstring strKey);

	BOOL deleteImage(wstring strKey);

	BOOL deleteAll(void);

	void render(wstring strKey, HDC hdc, int destX, int destY);
	void render(wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(wstring strKey, HDC hdc, int destX, int destY);
	void frameRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(wstring strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	void alphaRender(wstring strKey, HDC hdc, BYTE alpha);
	void alphaRender(wstring strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void alphaFrameRender(wstring strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);


	void aniRender(wstring strKey, HDC hdc, int destX, int destY, animation* ani);
	void aniAlphaRender(wstring strKey, HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	



	//getter
	wstring FindKeyByImage(image* img);

	imageManager();
	~imageManager();
};

