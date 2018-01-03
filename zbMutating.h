#pragma once
#include "Building.h"

#include "zuLarva.h"

class zbMutating : public Building
{
private:
	BUILDINGNUM_ZERG		_beforeBuildingNum;
	BUILDINGNUM_ZERG		_nextBuildingNum;

	Building*				_beforeBuilding;
	Building*				_nextBuilding;


	FLOAT					_buildHP;

	vector<zuLarva*>		_vLarva;



private:
	void initNextBuilding(POINT ptTile);
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);
	void initProcessing(void);

	//상속받은 가상함수
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);
	void updateProcessing(void);

	void procCommands(void);



public:
	zbMutating(PLAYER playerNum, BUILDINGNUM_ZERG buildingNum);
	zbMutating(PLAYER playerNum, BUILDINGNUM_ZERG buildingNum, Building* beforeBuilding);
	~zbMutating();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);




public:
	inline vector<zuLarva*> getLarvas(void) { return _vLarva; }

};

