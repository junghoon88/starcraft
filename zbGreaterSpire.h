#pragma once
#include "Building.h"
class zbGreaterSpire : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbGreaterSpire(PLAYER playerNum);
	~zbGreaterSpire();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

