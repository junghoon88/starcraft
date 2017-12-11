#pragma once
#include "Building.h"
class zbEvolutionChamber : public Building
{
public:
	zbEvolutionChamber();
	~zbEvolutionChamber();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

