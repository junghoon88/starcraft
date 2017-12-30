#pragma once
#include "Unit.h"

#include "zergProductionInfo.h"

class zuInfestedTerran : public Unit
{
private:
	zergProductionInfo* _zergProductionInfo;

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);

public:
	zuInfestedTerran(PLAYER playerNum);
	~zuInfestedTerran();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);

	void procCommands(void);


};

