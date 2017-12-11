#pragma once
#include "Unit.h"
class zuBroodling : public Unit
{
public:
	zuBroodling();
	~zuBroodling();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

