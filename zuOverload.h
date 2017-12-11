#pragma once
#include "Unit.h"
class zuOverload : public Unit
{
public:
	zuOverload();
	~zuOverload();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

