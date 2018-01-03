#pragma once
#include "Unit.h"


enum WORKSTATE
{
	WORKSTATE_IDLE,
	WORKSTATE_MOVETO_MINERAL,
	WORKSTATE_WAITING_MINERAL,
	WORKSTATE_GATHERING_MINERAL,
	WORKSTATE_RETURN_MINERAL,
	WORKSTATE_MOVETO_GAS,
	WORKSTATE_WAITING_GAS,
	WORKSTATE_GATHERING_GAS,
	WORKSTATE_RETURN_GAS
};


class zuDrone : public Unit
{
private:

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);

public:
	zuDrone(PLAYER playerNum);
	~zuDrone();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);

	void procCommands(void);


};

