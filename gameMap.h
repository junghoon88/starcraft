#pragma once
#include "gameNode.h"
#include "tileNode.h"

class gameMap : public gameNode
{
private:

public:
	gameMap();
	~gameMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
