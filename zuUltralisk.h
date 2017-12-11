#pragma once
#include "Unit.h"
class zuUltralisk : public Unit
{
public:
	zuUltralisk();
	~zuUltralisk();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

