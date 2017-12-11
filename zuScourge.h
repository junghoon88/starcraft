#pragma once
#include "Unit.h"
class zuScourge : public Unit
{
public:
	zuScourge();
	~zuScourge();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

