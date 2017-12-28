#pragma once
#include "Building.h"
class zbHydraliskDen : public Building
{
public:
	zbHydraliskDen();
	~zbHydraliskDen();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

