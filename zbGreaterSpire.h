#pragma once
#include "Building.h"
class zbGreaterSpire : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

	//��ӹ��� �����Լ�
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);
	void updateProcessing(void);
	void updateCommandSet(void);

	void procCommands(void);

public:
	zbGreaterSpire(PLAYER playerNum);
	~zbGreaterSpire();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

