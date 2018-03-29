#pragma once
#include "Unit.h"

class zuZergling : public Unit
{
private:

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);

public:
	zuZergling(PLAYER playerNum);
	~zuZergling();

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

