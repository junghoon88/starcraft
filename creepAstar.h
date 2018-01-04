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

	//���� Ÿ�Ͽ��� ���� �ִ� �� ã�� �Լ�
	vector<tile*> addOpenList(tile* currentTile, bool creepCheck = false);

public:
	creepAstar(gameMap* map);
	~creepAstar();

	//Ÿ�� ������ �Լ�
	void initTiles(void);
	void updateTileAttr(void);
	void clearTiles(void);
	void setTiles(POINT startPt);

	//��� Ž�� �Լ�
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

