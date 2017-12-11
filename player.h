#pragma once
#include "gameNode.h"
#include "Building.h"
#include "Unit.h"

#include "zergHeader.h"


class player : public gameNode
{
private:
	vector<Building*>				_vBuildings;
	vector<Building*>::iterator		_viBuildings;
	vector<Unit*>					_vUnits;
	vector<Unit*>::iterator			_viUnits;

	//플레이어 정보
	PLAYER							_playerNum;	
	BOOL							_isGaming;				//게임중인지


	zergUpgrade*					_zergUpgrade;
	//debug
	zuDrone* drone;


public:
	player();
	~player();

	HRESULT init(PLAYER playerNum);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);

};

