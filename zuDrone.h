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

	gameObject* _targetMineral;
	gameObject* _targetGas; //extractor

	FLOAT		_mineralGatheringTime;
	FLOAT		_mineralGatheringTimeMax;
	FLOAT		_gasGatheringTime;
	FLOAT		_gasGatheringTimeMax;


private:
	void initBaseStatus(void);
	void initBattleStatus(POINT pt);

	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);
	void updateCommandSet(void);

	void procCommands(void);

	void updateWorkState(void);


	void gatheringMineral(void);
	void gatheringGas(void);
	void returnCargo(void);

	void rotateToTarget(gameObject* obj);


	gameObject* findOtherMineral(void);
	gameObject* findCargo(void);

public:
	zuDrone(PLAYER playerNum);
	~zuDrone();

	HRESULT init(POINT pt);
	void release(void);
	void update(void);
	void render(void);

};

