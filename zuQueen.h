#pragma once
#include "Unit.h"

#include "zergProductionInfo.h"

class zuQueen : public Unit
{
private:
	zergProductionInfo* _zergProductionInfo;

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);

public:
	zuQueen(PLAYER playerNum);
	~zuQueen();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);

	void procCommands(void);

};

