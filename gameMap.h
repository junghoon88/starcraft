#pragma once
#include "gameNode.h"
#include "tileNode.h"

class nrMineral;
class nrGas;


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

	image*				_miniMapBackground;

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
	nrGas* findGas(POINT ptTile);

public:
	typedef tagTile(*pTiles)[TILEY];

	inline pTiles getTiles(void) { return _tiles; }

	inline vector<nrMineral*> getVMineral(void) { return _vMineral; }
	inline vector<nrGas*> getVGas(void) { return _vGas; } 

	inline image* getMinimapBackground(void) { return _miniMapBackground; }

	inline POINT getLocationP1(void) { return _locationP1; }
	inline POINT getLocationP2(void) { return _locationP2; }

};
