#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	POINT _pt;
	float _width;
	RECT _rcProgress;

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(TCHAR* name, int x, int y, int width, int height);
	HRESULT init(TCHAR* topImage, TCHAR* bottomImage, float x, float y, int width, int height);
	HRESULT init(TCHAR* topImage, TCHAR* bottomImage, float x, float y, int width, int height, TCHAR* foldername);
	void release(void);
	void update(void);
	void render(TCHAR* name);
	void render(void);

	void setGauge(float currentGauge, float maxGauge);

public:
	inline void setX(int x) { _pt.x = x; }
	inline void setY(int y) { _pt.y = y; }

	inline float getWidth(void) { return _width; }
	inline RECT getRect(void) { return _rcProgress; }
};

