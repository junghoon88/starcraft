#pragma once
#include "gameNode.h"
#include "loading.h"

class sceneInit : public gameNode
{
private:
	loading* _loading;

private:
	void initImage(void);
	void initSound(void);


	void initImageNeutralResource(void);
	void initImageMaptoolTiles(void);
	void initImageGamemapTiles(void);
	void initImageInterface(void);
	void initImageZergUnits(void);
	void initImageZergBuildings(void);
	void initImageZergDeath(void);
	void initImageZergBullet(void);

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	sceneInit();
	~sceneInit();
};

