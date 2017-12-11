#pragma once
#include "Unit.h"
class zuQueen : public Unit
{
public:
	zuQueen();
	~zuQueen();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

