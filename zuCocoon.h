#pragma once
#include "Unit.h"
class zuCocoon : public Unit
{
public:
	zuCocoon();
	~zuCocoon();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

