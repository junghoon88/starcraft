#pragma once
#include "Unit.h"
class zuZergEgg : public gameNode
{
public:
	zuZergEgg();
	~zuZergEgg();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

