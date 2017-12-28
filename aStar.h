#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include "gameMap.h"

class aStar : public gameNode
{
private:
	vTile _vTotalList;	// ��Ż Ÿ��
	vTile _vOpenList;	// �� �� �ִ� Ÿ��
	vTile _vCloseList;	// ���� ����� Ÿ��

	tile* _staTile;		// ���� Ÿ��
	tile* _endTile;		// ��   Ÿ��
	tile* _curTile;		// ���� Ÿ��

	bool _valid;

	gameMap* _map;

	int _findCnt;
	int _findCntMax;

public:
	aStar();
	~aStar();

	HRESULT init(void);

	//Ÿ�� ������ �Լ�
	void initTiles(void);
	void setTiles(POINT startPt, POINT endPt);


	//���� Ÿ�Ͽ��� ���� �ִ� �� ã�� �Լ�
	vTile addOpenList(tile* currentTile);
	//��� Ž�� �Լ�
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

