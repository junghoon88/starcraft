#pragma once
#include "Unit.h"
class zuLerkerEgg : public Unit
{
public:
	zuLerkerEgg();
	~zuLerkerEgg();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

