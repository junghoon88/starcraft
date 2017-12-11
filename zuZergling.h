#pragma once
#include "Unit.h"
class zuZergling : public Unit
{
public:
	zuZergling();
	~zuZergling();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

