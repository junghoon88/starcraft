#pragma once

#include "gameMap.h"

#include "creepAstar.h"

struct tagCreep
{
	POINT pt;

	BOOL  isSpreading;
	BOOL  isDisappearing;
};


class creepManager
{
private:
	vector<tagCreep>	_vCreeps;

	creepAstar* _aStar;
	gameMap*	_gameMap;

private:
	tagCreep* findCreep(POINT pt);
	void updateSpread(void);
	void updateDisappear(void);




public:
	creepManager();
	~creepManager();

	void init(gameMap* map);
	void update(void);

	void addCreep(POINT ptTile, POINT size);
	void deleteCreep(POINT ptTile, POINT size);


public:
};

