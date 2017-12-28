#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include "gameMap.h"

class aStar : public gameNode
{
private:
	vTile _vTotalList;	// 토탈 타일
	vTile _vOpenList;	// 갈 수 있는 타일
	vTile _vCloseList;	// 가장 가까운 타일

	tile* _staTile;		// 시작 타일
	tile* _endTile;		// 끝   타일
	tile* _curTile;		// 현재 타일

	bool _valid;

	gameMap* _map;

	int _findCnt;
	int _findCntMax;

public:
	aStar();
	~aStar();

	HRESULT init(void);

	//타일 셋팅할 함수
	void initTiles(void);
	void setTiles(POINT startPt, POINT endPt);


	//현재 타일에서 갈수 있는 길 찾는 함수
	vTile addOpenList(tile* currentTile);
	//경로 탐색 함수
	void pathFinder(tile* currentTile);

	void clearTiles(void);
	tile* getTile(POINT tilePt);


	void release(void);
	void update(void);
	void render(void);


public:
	inline void setLinkAdressGameMap(gameMap* map) { _map = map; }
	inline vTile getTotalList(void) { return _vTotalList; }
	inline void setTotalList(vTile vTotalList) { _vTotalList = vTotalList; }
	inline vTile getCloseList(void) { return _vCloseList; }

	inline tile* getStartTile(void) { return _staTile; }

	inline void setAttribute(int x, int y, DWORD attr) { _vTotalList[x + y*TILEX]->setAttribute(attr); }

};

