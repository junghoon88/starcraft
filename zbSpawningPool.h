#pragma once
#include "Building.h"
class zbSpawningPool : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbSpawningPool(PLAYER playerNum);
	~zbSpawningPool();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

