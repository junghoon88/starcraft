#pragma once
#include "Building.h"
class zbSunkenColony : public Building
{
public:
	zbSunkenColony();
	~zbSunkenColony();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

