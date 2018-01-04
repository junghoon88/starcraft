#pragma once

#include "gameMap.h"
#include "tile.h"
#include "tileNode.h"

class creepAstar
{
private:
	vTile _vTotalList;
	vTile _vOpenList;

	tile* _startTile;
	tile* _nextTile;

	gameMap*			_map;

	int _cost;
	int _costMax;

private:

	//현재 타일에서 갈수 있는 길 찾는 함수
	vector<tile*> addOpenList(tile* currentTile, bool creepCheck = false);

public:
	creepAstar(gameMap* map);
	~creepAstar();

	//타일 셋팅할 함수
	void initTiles(void);
	void updateTileAttr(void);
	void clearTiles(void);
	void setTiles(POINT startPt);

	//경로 탐색 함수
	BOOL findCloseCreep(tile* currentTile, int cost = 0);
	void findCreepList(tile* currentTile, int cost = 0);
	tile* findFarCreep(void);

public:
	inline int getCostMax(void) { return _costMax; }

	inline vTile getVOpenList(void) { return _vOpenList; }

	inline tile* getNextTile(void) { return _nextTile; }
	inline tile* findTile(int idX, int idY) { return _vTotalList[idY * TILEX + idX]; }
	inline tile* findTile(POINT ptTile) { return _vTotalList[ptTile.y * TILEX + ptTile.x]; }


};

