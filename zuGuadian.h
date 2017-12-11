#pragma once
#include "Unit.h"
class zuGuadian : public Unit
{
public:
	zuGuadian();
	~zuGuadian();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

