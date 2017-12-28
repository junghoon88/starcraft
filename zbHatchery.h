#pragma once
#include "Building.h"

#include "zuLarva.h"

class zbHatchery : public Building
{
private:
	vector<zuLarva*>	_vLarva;

	FLOAT				_larvaResponeTime;


private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);
	void initLarva(UINT num);


public:
	zbHatchery(PLAYER playerNum);
	~zbHatchery();

	HRESULT init(POINT ptTIle);
	HRESULT init(POINT ptTile, UINT larvaNum);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

public:
	vector<zuLarva*> getLarvas(void) { return _vLarva; }

};

