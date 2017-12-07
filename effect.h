#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;
	int _y;

	image* _effectImage;
	animation* _effectAnimation;
	BOOL _isRunning;
	float _elapsedTime;

public:
	HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	HRESULT init(image* effectImage, int fps, float elapsedTime);
	void release(void);
	void update(void);
	void render(void);
	void render(ZORDER zorder);

	void startEffect(int x, int y);
	void startEffect(POINT pt);

	virtual void killEffect(void);

	BOOL getIsRunning(void) { return _isRunning; }
	

	effect();
	~effect();
};

