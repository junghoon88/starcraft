#pragma once
#include "Building.h"
class zbLair : public Building
{
private:
	vector<zuLarva*>	_vLarva;

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

public:
	zbLair(PLAYER playerNum);
	~zbLair();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

public:
	vector<zuLarva*> getLarvas(void) { return _vLarva; }

};

