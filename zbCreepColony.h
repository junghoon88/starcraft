#pragma once
#include "Building.h"
class zbCreepColony : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbCreepColony(PLAYER playerNum);
	~zbCreepColony();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

