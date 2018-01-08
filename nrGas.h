#pragma once

#include "gameObject.h"

class nrGas : public gameObject
{
	RECT	_rcTile;
	RECT	_rcBody;

	image*	_img;

public:
	nrGas(int tilex, int tiley);
	~nrGas();

	HRESULT init(UINT amount);
	void release(void);
	void update(void);	
	void render(void);	
	void getChar(WPARAM wParam);

	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);


public:
	inline RECT	getRectTile(void) { return _rcTile; }
	inline RECT	getRectBody(void) { return _rcBody; }
	inline image* getImage(void) { return _img; }

};

