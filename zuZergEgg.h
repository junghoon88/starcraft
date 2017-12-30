#pragma once
#include "Unit.h"

#include "zergProductionInfo.h"

#include "progressBar.h"

class zuZergEgg : public Unit
{
private:
	Unit * _nextUnit;

	zergProductionInfo* _zergProductionInfo;

	UNITNUM_ZERG	_nextUnitNum;


	FLOAT					_buildTime;
	FLOAT					_buildTimeMax;


	progressBar*			_progressBar;

	BOOL			_complete;

private:
	void initNextUnit(POINT pt);
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);

public:
	zuZergEgg(PLAYER playerNum, UNITNUM_ZERG nextUnitNum);
	~zuZergEgg();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);

	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);

	void updateProgressBar(void);

	void procCommands(void);

};

