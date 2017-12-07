#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include "gameMap.h"

//1. 이동가능한 타일을 찾는다. (각 타일별로 소모값을 넣는다.)
//2. 이동가능한 타일 중에서 그 위치에서 공격할 수 있는 타일을 찾는다.
//3. 공격 가능한 타일중에서 상대편 적의 HP가 가장 낮은 애를 공격한다.


class aStar : public gameNode
{
private:
	typedef vector<tile*> vTile;
	typedef vector<tile*>::iterator viTile;

	typedef map<int, tile*> mTile;
	typedef map<int, tile*>::iterator miTile;

private:
	vTile _vTotalList;	// 토탈 타일
	vTile _vOpenList;	// 갈 수 있는 타일
	mTile _mAttackList;	// 공격 가능한 위치, 적 타일

	tile* _staTile;		// 시작 타일



	gameMap* _map;

	int _cost;
	int _costMax;

	POINT _tileMax;

private:
	tile* findTile(int idX, int idY);

public:
	aStar();
	~aStar();

	HRESULT init(gameMap* map);
	void release(void);
	void update(void);
	void render(void);


	//타일 셋팅할 함수
	void initTiles(void);
	void resetTilesAttr(void);
	void setTiles(POINT startPt, int costMax);

	//현재 타일에서 갈수 있는 길 찾는 함수
	vector<tile*> addOpenList(tile* currentTile);
	//경로 탐색 함수
	void findOpenList(tile* currentTile, int cost = 0);

	//현재 타일에서 공격 가능한지 찾는 함수

	POINT findCloseTile(POINT st, POINT ed);

	void clearTiles(void);
	tile* getTile(POINT tilePt);

public:
	inline vector<tile*> getOpenList(void) { return _vOpenList; }
};

