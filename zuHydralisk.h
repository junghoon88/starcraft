#pragma once
#include "Unit.h"
class zuHydralisk : public Unit
{
public:
	zuHydralisk();
	~zuHydralisk();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

