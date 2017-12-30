#pragma once
#include "Building.h"
class zbDefilerMound : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbDefilerMound(PLAYER playerNum);
	~zbDefilerMound();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

