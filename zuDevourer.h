#pragma once
#include "Unit.h"

#include "zergProductionInfo.h"

class zuDevourer : public Unit
{
private:
	zergProductionInfo* _zergProductionInfo;

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);


public:
	zuDevourer(PLAYER playerNum);
	~zuDevourer();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);

	void procCommands(void);


};

