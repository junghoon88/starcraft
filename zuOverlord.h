#pragma once
#include "Unit.h"


class zuOverlord : public Unit
{
private:

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);

public:
	zuOverlord(PLAYER playerNum);
	~zuOverlord();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);

	void procCommands(void);

};

