#pragma once
#include "Building.h"
class zbSpawningPool : public Building
{
public:
	zbSpawningPool();
	~zbSpawningPool();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

