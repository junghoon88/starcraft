#pragma once
#include "Unit.h"

class zuDrone : public Unit
{
public:
	zuDrone();
	~zuDrone();

	HRESULT init(PLAYER playerNum, POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);



};

