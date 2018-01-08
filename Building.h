#pragma once
#include "gameObject.h"

#include "zergUpgrade.h"

#include "zuLarva.h"

//���漱��
class Unit;

class Building : public gameObject
{
protected:

public:
	Building();
	~Building();

	virtual HRESULT init(POINT ptTile);
	virtual HRESULT init(POINT ptTile, UINT larvaNum);
	virtual void release(void);
	virtual void update(void);
	virtual void render(int imgOffsetX = 0, int imgOffsetY = 0);

	//���׷��̵尡 �Ϸ�Ǿ��� �� BattleStatus �� ������Ʈ�Ѵ�.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);
	virtual void updateProcessing(void);
	virtual void updateCommandSet(void);
	virtual void checkDead(void);

	virtual void procCommands(void);


public:
	//getter, setter (�ڽ��Լ���)



};
typedef vector<Building*>				vBuildings;
typedef vector<Building*>::iterator		vBuildingsIter;

