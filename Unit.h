#pragma once
#include "gameObject.h"
#include "zergUpgrade.h"

#include "aStar.h"

//전방선언
class Building;
class Unit;

class Unit : public gameObject
{
private:
	UINT _colnum;
	UINT _colsequence;

public:
	Unit();
	~Unit();

	virtual HRESULT init(POINT pt);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//업그레이드가 완료되었을 때 BattleStatus 를 업데이트한다.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);
	virtual void updateCommandSet(void);
	virtual void checkDead(void);


	//커맨드를 처리한다.
	virtual void procCommands(void);


	//move
	void moveGround(void);
	void moveAir(void);
	void moveToPoint(POINT ptEd);
	void moveComplete(void);

	//attack
	void attackProc(void);
	BOOL isInAttackRange(gameObject* target);
	gameObject* findEnemy(void);


	void checkCloseList(void);

	void setImageFrameForAngle(void);

	bool isInTargetPoint(void);

	//움직이지 않는 유닛은 맵에 등록한다.
	void stopUnitRegisterMap(void);

public:
	void collisionMoveOffset(int x, int y);


private:
	void collision(void);

	void collisionUnit(UINT st, UINT ed);
	void collisionBuilding(UINT st, UINT ed);
	void collisionMineral(UINT st, UINT ed);
	void collisionGas(UINT st, UINT ed);


};
typedef vector<Unit*>					vUnits;
typedef vector<Unit*>::iterator			vUnitsIter;


