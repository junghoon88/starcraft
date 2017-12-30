#pragma once
#include "Building.h"
class zbUltraliskCavern : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbUltraliskCavern(PLAYER playerNum);
	~zbUltraliskCavern();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

