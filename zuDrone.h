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
	WORKSTATE	_workState;
	UINT		_hangingMineral;	//0이면 안들고 있는 것.
	UINT		_hangingGas;		//0이면 안들고 있는 것.

public:
	zuDrone();
	~zuDrone();

	HRESULT init(PLAYER playerNum, POINT pt);
	void release(void);
	void update(void);
	void render(void);
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);


};

