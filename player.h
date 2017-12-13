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
	vBuildings		_vBuildings;			//�÷��̾ ������ �ִ� �ǹ���
	vUnits			_vUnits;				//�÷��̾ ������ �ִ� ���ֵ�
	vBuildings		_vBuildingsInCamera;	//ī�޶� �����ִ� �ǹ���
	vUnits			_vUnitsInCamera;		//ī�޶� �����ִ� ���ֵ�



	//�÷��̾� ����
	PLAYER							_playerNum;	
	RACES							_races;
	BOOL							_isGaming;				//����������


	zergUpgrade*					_zergUpgrade;

	//������
	gameMap*						_gameMap;				//���Ӹ�(Ÿ������) -> sceneBattle ���� ��ũ�� �޴´�.
	fog*							_fog;					//�Ȱ�


	aStar*							_aStar;					//��ã�� A* �˰���


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

