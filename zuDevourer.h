#pragma once
#include "Unit.h"
class zuDevourer : public Unit
{
public:
	zuDevourer();
	~zuDevourer();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

