#pragma once
#include "Unit.h"
class zuLurker : public Unit
{
public:
	zuLurker();
	~zuLurker();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

