#pragma once
#include "gameObject.h"
#include "zergUpgrade.h"

#include "aStar.h"

//���漱��
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

	//���׷��̵尡 �Ϸ�Ǿ��� �� BattleStatus �� ������Ʈ�Ѵ�.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);
	virtual void updateCommandSet(void);
	virtual void checkDead(void);


	//Ŀ�ǵ带 ó���Ѵ�.
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

	//�������� �ʴ� ������ �ʿ� ����Ѵ�.
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


