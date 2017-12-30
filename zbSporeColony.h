#pragma once
#include "Building.h"
class zbSporeColony : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbSporeColony(PLAYER playerNum);
	~zbSporeColony();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

