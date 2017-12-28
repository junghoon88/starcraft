#pragma once
#include "Unit.h"

#include "zergProductionInfo.h"

class zuZergEgg : public Unit
{
private:
	zergProductionInfo* _zergProductionInfo;

	UNITNUM_ZERG	_nextUnitNum;
	BOOL			_complete;


private:
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

	void procCommands(void);

};

