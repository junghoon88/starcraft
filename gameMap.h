#pragma once
#include "gameNode.h"
#include "tileNode.h"

class gameMap : public gameNode
{
private:
	//Ÿ������
	tagTile _tiles[TILEX][TILEY];
	//Ÿ���̹���
	image*	_imgTiles[TILEX][TILEY];

public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

private:
	//�������� �׸� �� �ε��Լ�
	void loadData(int num);
	void setTileImage(void);

	void renderTiles(void);


};
