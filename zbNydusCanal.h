#pragma once
#include "Building.h"
class zbNydusCanal : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbNydusCanal(PLAYER playerNum);
	~zbNydusCanal();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

