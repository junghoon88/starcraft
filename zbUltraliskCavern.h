#pragma once
#include "Building.h"
class zbUltraliskCavern : public Building
{
private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

	//상속받은 가상함수
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);
	void updateProcessing(void);
	void updateCommandSet(void);

	void procCommands(void);
public:
	zbUltraliskCavern(PLAYER playerNum);
	~zbUltraliskCavern();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);

};

