#pragma once
#include "Building.h"
class zbQueensNest : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbQueensNest(PLAYER playerNum);
	~zbQueensNest();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

