#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	float _gaugeWidth;
	RECT _rcProgress;

	image* _progressBarTop;
	image* _progressBarBottom;

	int _imgWidth;
	int _imgHeight;

public:
	progressBar();
	~progressBar();

	HRESULT init(TCHAR* name);
	HRESULT init(TCHAR* topImage, TCHAR* bottomImage);
	
	void release(void);
	void update(void);
	void render(void);
	void ZRender(ZORDER zorder);

	void setGauge(float currentGauge, float maxGauge);

public:
	inline float getGaugeWidth(void) { return _gaugeWidth; }
	inline RECT getRect(void) { return _rcProgress; }
	inline void setRect(RECT rc) { _rcProgress = rc; }

	inline void setPointLT(POINT pt) { _rcProgress = RectMake(pt.x, pt.y, _imgWidth, _imgHeight); }
	inline void setPointCC(POINT pt) { _rcProgress = RectMakeCenter(pt.x, pt.y, _imgWidth, _imgHeight); }

	inline void setPointLT(int x, int y) { _rcProgress = RectMake(x, y, _imgWidth, _imgHeight); }
	inline void setPointCC(int x, int y) { _rcProgress = RectMakeCenter(x, y, _imgWidth, _imgHeight); }

};

