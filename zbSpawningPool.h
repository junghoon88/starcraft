#pragma once
#include "Building.h"
class zbSpawningPool : public Building
{
public:
	zbSpawningPool();
	~zbSpawningPool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

