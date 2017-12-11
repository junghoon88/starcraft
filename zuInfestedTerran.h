#pragma once
#include "Unit.h"
class zuInfestedTerran : public Unit
{
public:
	zuInfestedTerran();
	~zuInfestedTerran();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

