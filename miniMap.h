#pragma once
#include "gameNode.h"
#include "tileNode.h"


class miniMap : public gameNode
{
private:
	image*		_img;
	RECT		_rc;
	RECT		_rcMiniMapCamera;

	COLORREF	_color[TILEX][TILEY];



public:
	miniMap();
	~miniMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	inline RECT getRect(void) { return _rc; }

};

