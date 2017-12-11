#pragma once
#include "gameNode.h"
#include "tileNode.h"

class gameMap : public gameNode
{
private:
	//타일정보
	tagTile _tiles[TILEX][TILEY];
	//타일이미지
	image*	_imgTiles[TILEX][TILEY];

public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

private:
	//맵툴에서 그린 맵 로드함수
	void loadData(int num);
	void setTileImage(void);

	void renderTiles(void);


};
