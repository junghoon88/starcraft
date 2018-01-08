#pragma once
#include "gameObject.h"

#include "zergUpgrade.h"

#include "zuLarva.h"

//전방선언
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

	//업그레이드가 완료되었을 때 BattleStatus 를 업데이트한다.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);
	virtual void updateProcessing(void);
	virtual void updateCommandSet(void);
	virtual void checkDead(void);

	virtual void procCommands(void);


public:
	//getter, setter (자식함수용)



};
typedef vector<Building*>				vBuildings;
typedef vector<Building*>::iterator		vBuildingsIter;

