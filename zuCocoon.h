#pragma once
#include "Unit.h"

class zuCocoon : public Unit
{
private:
	Unit * _nextUnit;

	UNITNUM_ZERG	_nextUnitNum;

private:
	void initNextUnit(POINT pt);
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);
	void initProcessing(void);

public:
	zuCocoon(PLAYER playerNum, UNITNUM_ZERG nextUnitNum);
	~zuCocoon();

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

