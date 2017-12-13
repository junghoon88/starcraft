#pragma once
#include "gameNode.h"
#include "Building.h"
#include "Unit.h"

#include "gameMap.h"
#include "fog.h"

#include "zergHeader.h"

#include "aStar.h"


class player : public gameNode
{
private:
	vBuildings		_vBuildings;			//플레이어가 가지고 있는 건물들
	vUnits			_vUnits;				//플레이어가 가지고 있는 유닛들
	vBuildings		_vBuildingsInCamera;	//카메라에 보여주는 건물들
	vUnits			_vUnitsInCamera;		//카메라에 보여주는 유닛들



	//플레이어 정보
	PLAYER							_playerNum;	
	RACES							_races;
	BOOL							_isGaming;				//게임중인지


	zergUpgrade*					_zergUpgrade;

	//맵정보
	gameMap*						_gameMap;				//게임맵(타일정보) -> sceneBattle 에서 링크로 받는다.
	fog*							_fog;					//안개


	aStar*							_aStar;					//길찾기 A* 알고리즘


public:
	player();
	~player();

	HRESULT init(PLAYER playerNum, RACES races);
	void release(void);
	void update(void);
	void render(fog* fog);

private:
	void checkInCamera(void);

public:
	inline void setLinkAdressGamemap(gameMap* map) { _gameMap = map; }


	inline vBuildings getBuildings(void) { return _vBuildings; }
	inline vUnits    getUnits(void) { return _vUnits; }
	inline vBuildings getBuildingsInCamera(void) { return _vBuildingsInCamera; }
	inline vUnits    getUnitsInCamera(void) { return _vUnitsInCamera; }


	inline RACES getRaces(void) { return _races; }


	inline zergUpgrade* getZergUpgrade(void) { return _zergUpgrade; }
	inline fog* getFog(void) { return _fog; }

};

