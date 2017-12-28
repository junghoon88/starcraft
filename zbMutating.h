#pragma once
#include "Building.h"

#include "zergProductionInfo.h"

#include "progressBar.h"

class zbMutating : public Building
{
private:
	Building*				_beforeBuilding;
	Building*				_nextBuilding;

	zergProductionInfo*		_zergProductionInfo;


	FLOAT					_buildTime;
	FLOAT					_buildTimeMax;
	FLOAT					_buildHP;

	progressBar*			_progressBar;

	BOOL					_complete;

private:
	void initNextBuilding(POINT ptTile);
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

	//상속받은 가상함수
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);

	void updateProgressBar(void);



public:
	zbMutating(PLAYER playerNum, BUILDINGNUM_ZERG buildingNum);
	zbMutating(PLAYER playerNum, BUILDINGNUM_ZERG buildingNum, Building* beforeBuilding);
	~zbMutating();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);


	void procCommands(void);

};

