#pragma once
#include "Building.h"
class zbEvolutionChamber : public Building
{
public:
	zbEvolutionChamber();
	~zbEvolutionChamber();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

