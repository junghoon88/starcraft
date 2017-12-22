#pragma once
#include "gameNode.h"
#include "tileNode.h"

#include "nrMineral.h"
#include "nrGas.h"


class gameMap : public gameNode
{
private:
	//타일정보
	tagTile _tiles[TILEX][TILEY];
	//타일이미지
	image*	_imgTiles[TILEX][TILEY];

	vector<nrMineral*>  _vMineral;
	vector<nrGas*>		_vGas;

	POINT				_locationP1;
	POINT				_locationP2;

public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

private:
	//맵툴에서 그린 맵 로드함수
	void loadData(void);
	void setTileImage(void);
	void createNeutralResource(void);

	//render
	void renderTiles(void);

	void renderObject(void);

public:
	typedef tagTile(*pTiles)[TILEY];

	inline pTiles getTiles(void) { return _tiles; }

};
