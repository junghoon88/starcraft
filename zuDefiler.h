#pragma once
#include "Unit.h"
class zuDefiler : public Unit
{
public:
	zuDefiler();
	~zuDefiler();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

