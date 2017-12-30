#pragma once
#include "Building.h"
class zbHive : public Building
{
private:
	vector<zuLarva*>	_vLarva;

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbHive(PLAYER playerNum);
	~zbHive();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

public:
	vector<zuLarva*> getLarvas(void) { return _vLarva; }

};

