#pragma once
#include "Building.h"
class zbSporeColony : public Building
{
public:
	zbSporeColony();
	~zbSporeColony();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

