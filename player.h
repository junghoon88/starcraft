#pragma once
#include "gameNode.h"
#include "gameObject.h"
#include "Building.h"
#include "Unit.h"

#include "gameMap.h"
#include "fog.h"

#include "zergHeader.h"

#include "aStar.h"

#include "gameController.h"
#include "gameObjectPool.h"

class player : public gameNode
{
private:
	//static 변수

private:
	UINT							_myMineral;
	UINT							_myGas;
	FLOAT							_myControl;
	FLOAT							_myControlMax;

	vUnits							_vUnits;				//플레이어가 가지고 있는 유닛들
	vUnits							_vUnitsInCamera;		//카메라에 보여주는 유닛들
	vBuildings						_vBuildings;			//플레이어가 가지고 있는 건물들
	vBuildings						_vBuildingsInCamera;	//카메라에 보여주는 건물들



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
	
	//게임오브젝트풀
	//gameObjectPool*					_gameObjectPool;

public:
	player();
	~player();

	HRESULT init(PLAYER playerNum, RACES races);
	void release(void);
	void update(void);
	void render(fog* fog);

	bool isHaveBuilding(BUILDINGNUM_ZERG num);

	bool useResource(UINT mineral, UINT gas);
	bool useResource(UINT mineral, UINT gas, float control);


	void checkUnitValid(void);
	void checkBuildingVaild(void);




private:
	void checkInCamera(void);

public:
	inline void setLinkAdressGamemap(gameMap* map) { _gameMap = map; }
	//inline void setLinkAdressGameObjectPool(gameObjectPool* pool) { _gameObjectPool = pool; }

	inline void addUnit(Unit* unit) { _vUnits.push_back(unit); }
	inline void addBuilding(Building* building) { _vBuildings.push_back(building); }


	inline vUnits		getUnits(void) { return _vUnits; }
	inline vUnits		getUnitsInCamera(void)		{ return _vUnitsInCamera; }
	inline vBuildings	getBuildings(void)			{ return _vBuildings; }
	inline vBuildings	getBuildingsInCamera(void)	{ return _vBuildingsInCamera; }

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

