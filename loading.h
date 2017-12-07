#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,		//이미지 초기화에 따른 열거
	LOAD_KIND_IMAGE_1,
	LOAD_KIND_IMAGE_2,
	LOAD_KIND_FRAMEIMAGE_0,
	LOAD_KIND_FRAMEIMAGE_1,
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagImageResource
{
	//wstring keyName;
	TCHAR keyName[256];
	//const TCHAR* fileName;
	TCHAR fileName[256];
	float x, y;
	int width, height;
	int frameX, frameY;
	bool trans;
	COLORREF transColor;
	bool blend;
};

struct tagSoundResource
{
	TCHAR keyName[256];
	TCHAR fileName[256];
	bool bgm;
	bool loop;
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;

public:
	loadItem();
	~loadItem();

	HRESULT initForImage(const TCHAR* keyName, int width, int height, bool blend = FALSE);
	HRESULT initForImage(const TCHAR* keyName, const TCHAR* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	HRESULT initForImage(const TCHAR* keyName, const TCHAR* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);

	HRESULT initForFrameImage(const TCHAR* keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	HRESULT initForFrameImage(const TCHAR* keyName, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);

	HRESULT initForSound(const TCHAR* keyName, const TCHAR* fileName, bool bgm, bool loop);

	LOAD_KIND getLoadingKind() { return _kind; }

public:
	inline tagImageResource getImageResource(void) { return _imageResource; }
	inline tagSoundResource getSoundResource(void) { return _soundResource; }

};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;


	image* _background;
	progressBar* _loadingBar;

	int _currentGauge;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void loadImage(const TCHAR* keyName, int width, int height, bool blend = FALSE);
	void loadImage(const TCHAR* keyName, const TCHAR* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	void loadImage(const TCHAR* keyName, const TCHAR* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	void loadFrameImage(const TCHAR* keyName, const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	void loadFrameImage(const TCHAR* keyName, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE, bool blend = FALSE);
	void loadSound(const TCHAR* keyName, const TCHAR* fileName, bool bgm, bool loop);

	BOOL loadingImageDone();

	vector<loadItem*> getLoadItem() { return _vLoadItem; }


	loading();
	~loading();
};

