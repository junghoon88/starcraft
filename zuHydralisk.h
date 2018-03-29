#pragma once
#include "Unit.h"


class zuHydralisk : public Unit
{
private:

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);


public:
	zuHydralisk(PLAYER playerNum);
	~zuHydralisk();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);
	void updateCommandSet(void);

	void procCommands(void);

};

