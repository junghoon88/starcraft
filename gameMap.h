#pragma once
#include "gameNode.h"
#include "tileNode.h"

#include "nrMineral.h"
#include "nrGas.h"


class gameMap : public gameNode
{
private:
	//Ÿ������
	tagTile _tiles[TILEX][TILEY];
	//Ÿ���̹���
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
	//�������� �׸� �� �ε��Լ�
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
