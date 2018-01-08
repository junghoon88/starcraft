#pragma once
#include "gameNode.h"
#include "gameObject.h"
#include "Building.h"
#include "Unit.h"

#include "gameMap.h"
#include "fog.h"

#include "zergHeader.h"
#include "zergProductionInfo.h"

#include "aStar.h"

#include "gameController.h"

#include "creepManager.h"

#include "UnitCollision.h"

class player : public gameNode
{
private:
	//static 변수

private:
	UINT							_myMineral;
	UINT							_myGas;
	FLOAT							_myControl;
	FLOAT							_myControlMax;

	UINT							_showMineral;
	UINT							_showGas;


	vUnits							_vUnits;				//플레이어가 가지고 있는 유닛들
	vUnits							_vUnitsInCamera;		//카메라에 보여주는 유닛들
	vBuildings						_vBuildings;			//플레이어가 가지고 있는 건물들
	vBuildings						_vBuildingsInCamera;	//카메라에 보여주는 건물들

	//플레이어 정보
	PLAYER							_playerNum;	
	RACES							_races;
	BOOL							_isGaming;				//게임중인지


	zergUpgrade*					_zergUpgrade;
	zergProductionInfo*				_zergProductionInfo;

	vector<UPGRADE_ZERG>			_vZergUpgradeComplete;
	vector<EVOLUTION_ZERG>			_vZergEvolutionComplete;


	//맵정보
	gameMap*						_gameMap;				//게임맵(타일정보) -> sceneBattle 에서 링크로 받는다.
	fog*							_fog;					//안개
	creepManager*					_creepManager;

	//A*
	aStar*							_aStar;					//길찾기 A* 알고리즘
	HANDLE							_hAstarThread;
	HANDLE							_hCreepThread;
	HANDLE							_hCollisionThread;

	BOOL							_endThread;

	//interface
	gameController*					_gameController;

	UnitCollision*					_UnitCollision;


public:
	player();
	~player();

	HRESULT init(PLAYER playerNum, RACES races);
	void release(void);
	void update(void);
	void render(fog* fog);

	bool isHaveBuilding(BUILDINGNUM_ZERG num);


	bool canResource(UINT mineral, UINT gas);
	bool useResource(UINT mineral, UINT gas);
	bool useResource(UINT mineral, UINT gas, float control);
	inline void addResource(UINT mineral, UINT gas)		{ _myMineral += mineral; _myGas += gas; }


	void checkUnitValid(void);
	void checkBuildingVaild(void);

	void addUnit(Unit* unit);
	void addBuilding(Building* building);



private:
	void initStartUnit(void);

	void checkInCamera(void);
	void calcResource(void);
	void updateZergUpgrade(void);

public:
	inline void setLinkAdressGamemap(gameMap* map) { _gameMap = map; }
	inline void setLinkAdressZergProduction(zergProductionInfo* info) { _zergProductionInfo = info; }
	inline zergProductionInfo* getZergProductionInfo(void) { return _zergProductionInfo; }


	inline UINT	getMyMineral(void)		{ return _myMineral; }
	inline UINT	getMyGas(void)			{ return _myGas; }
	inline FLOAT getMyControl(void)		{ return _myControl; }
	inline FLOAT getMyControlMax(void)	{ return _myControlMax; }
	inline UINT	getShowMineral(void)	{ return _showMineral; }
	inline UINT	getShowGas(void)		{ return _showGas; }



	inline vUnits		getUnits(void) { return _vUnits; }
	inline vUnits		getUnitsInCamera(void)		{ return _vUnitsInCamera; }
	inline vBuildings	getBuildings(void)			{ return _vBuildings; }
	inline vBuildings	getBuildingsInCamera(void)	{ return _vBuildingsInCamera; }



	inline PLAYER getPlayerNum(void) { return _playerNum; }

	inline RACES getRaces(void) { return _races; }


	inline zergUpgrade* getZergUpgrade(void) { return _zergUpgrade; }
	inline void addZergUpgradeComplete(UPGRADE_ZERG upgrade)		{ _vZergUpgradeComplete.push_back(upgrade); }
	inline void addZergEvolutionComplete(EVOLUTION_ZERG evolution)	{ _vZergEvolutionComplete.push_back(evolution); }


	inline gameMap* getGamemap(void) { return _gameMap; }
	inline fog* getFog(void) { return _fog; }
	inline creepManager* getCreepManager(void) { return _creepManager; }

	
	inline aStar* getAstar(void) { return _aStar; }
	inline BOOL getEndThread(void) { return _endThread; }



	inline gameController* getGameController(void) { return _gameController; }

	inline UnitCollision* getUnitCollision(void) { return _UnitCollision; }

public:
	friend unsigned CALLBACK AstarThread(void* pArguments);
	friend unsigned CALLBACK CreepThread(void* pArguments);
	friend unsigned CALLBACK CollisionThread(void* pArguments);

};

