#pragma once
#include "Building.h"
class zbHydraliskDen : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbHydraliskDen(PLAYER playerNum);
	~zbHydraliskDen();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

