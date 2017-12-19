#pragma once
#include "gameNode.h"
#include "Building.h"
#include "Unit.h"

#include "gameMap.h"
#include "fog.h"

#include "zergHeader.h"

#include "aStar.h"

#include "gameController.h"

class player : public gameNode
{
private:
	//static 변수

private:
	vBuildings						_vBuildings;			//플레이어가 가지고 있는 건물들
	vUnits							_vUnits;				//플레이어가 가지고 있는 유닛들
	vBuildings						_vBuildingsInCamera;	//카메라에 보여주는 건물들
	vUnits							_vUnitsInCamera;		//카메라에 보여주는 유닛들



	//플레이어 정보
	PLAYER							_playerNum;	
	RACES							_races;
	BOOL							_isGaming;				//게임중인지


	zergUpgrade*					_zergUpgrade;

	//맵정보
	gameMap*						_gameMap;				//게임맵(타일정보) -> sceneBattle 에서 링크로 받는다.
	fog*							_fog;					//안개

	//A*
	aStar*							_aStar;					//길찾기 A* 알고리즘
	HANDLE							_hAstarThread;
	HANDLE							_hControllerThread;
	BOOL							_endThread;

	//interface
	gameController*					_gameController;


public:
	player();
	~player();

	HRESULT init(PLAYER playerNum, RACES races);
	void release(void);
	void update(void);
	void render(fog* fog);

	bool haveBuilding(BUILDINGNUM_ZERG num);

private:
	void checkInCamera(void);

public:
	inline void setLinkAdressGamemap(gameMap* map) { _gameMap = map; }


	inline vBuildings getBuildings(void) { return _vBuildings; }
	inline vUnits    getUnits(void) { return _vUnits; }
	inline vBuildings getBuildingsInCamera(void) { return _vBuildingsInCamera; }
	inline vUnits    getUnitsInCamera(void) { return _vUnitsInCamera; }

	inline PLAYER getPlayerNum(void) { return _playerNum; }

	inline RACES getRaces(void) { return _races; }


	inline zergUpgrade* getZergUpgrade(void) { return _zergUpgrade; }
	inline fog* getFog(void) { return _fog; }

	
	inline aStar* getAstar(void) { return _aStar; }
	inline BOOL getEndThread(void) { return _endThread; }

	inline gameController* getGameController(void) { return _gameController; }

public:
	friend unsigned CALLBACK AstarThread(void* pArguments);
	friend unsigned CALLBACK ControllerThread(void* pArguments);

};

