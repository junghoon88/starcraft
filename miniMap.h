#pragma once
#include "gameNode.h"

class miniMap : public gameNode
{
public:
	miniMap();
	~miniMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

