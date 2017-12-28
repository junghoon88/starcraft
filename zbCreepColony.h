#pragma once
#include "Building.h"
class zbCreepColony : public Building
{
public:
	zbCreepColony();
	~zbCreepColony();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

