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
	//static ����

private:
	vBuildings						_vBuildings;			//�÷��̾ ������ �ִ� �ǹ���
	vUnits							_vUnits;				//�÷��̾ ������ �ִ� ���ֵ�
	vBuildings						_vBuildingsInCamera;	//ī�޶� �����ִ� �ǹ���
	vUnits							_vUnitsInCamera;		//ī�޶� �����ִ� ���ֵ�



	//�÷��̾� ����
	PLAYER							_playerNum;	
	RACES							_races;
	BOOL							_isGaming;				//����������


	zergUpgrade*					_zergUpgrade;

	//������
	gameMap*						_gameMap;				//���Ӹ�(Ÿ������) -> sceneBattle ���� ��ũ�� �޴´�.
	fog*							_fog;					//�Ȱ�

	//A*
	aStar*							_aStar;					//��ã�� A* �˰���
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

