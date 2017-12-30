#pragma once
#include "Unit.h"

#include "zergProductionInfo.h"

class zuBroodling : public Unit
{
private:
	zergProductionInfo* _zergProductionInfo;

	FLOAT		_lifeTime;
	FLOAT		_lifeTimeMax;

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);

public:
	zuBroodling(PLAYER playerNum);
	~zuBroodling();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);

	void procCommands(void);

};

