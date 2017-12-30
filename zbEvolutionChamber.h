#pragma once
#include "Building.h"
class zbEvolutionChamber : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbEvolutionChamber(PLAYER playerNum);
	~zbEvolutionChamber();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

