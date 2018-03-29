#pragma once
#include "gameNode.h"

#include "gameObject.h"

enum BULLETNUM
{
	BULLETNUM_MUTALISK,
	BULLETNUM_GUADIAN,
	BULLETNUM_DEVOURER,
};

class bullets : public gameNode
{
private:
	BOOL		_valid;

	gameObject*	_master;
	gameObject*	_enemy;

	BULLETNUM	_bulletNum;
	DAMAGETYPE	_dmgType;
	FLOAT		_speed;
	image*		_img;
	POINT		_imgFrame;
	FLOAT		_imgFrameTime;
	ZORDER		_zorder;


	MYPOINT		_pt;
	RECT		_rc;

	FLOAT		_damage;
	POINT		_startPt;
	POINT		_endPt;
	FLOAT		_angle;



public:
	bullets(BULLETNUM bulletNum);
	~bullets();

	HRESULT init(gameObject* master, gameObject* enemy);
	void release(void);
	void update(void);
	void render(void);

public:
	inline BOOL getValid(void) { return _valid; }
	inline RECT getRect(void) { return _rc; }
};

typedef vector<bullets*> vBullets;
typedef vector<bullets*>::iterator vBulletsIter;

