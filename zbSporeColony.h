#pragma once
#include "Building.h"
class zbSporeColony : public Building
{
public:
	zbSporeColony();
	~zbSporeColony();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

