#pragma once
#include "Unit.h"
class zuLarva : public Unit
{
public:
	zuLarva();
	~zuLarva();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

