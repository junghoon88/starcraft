#pragma once
#include "Unit.h"
class zuMutalisk : public Unit
{
public:
	zuMutalisk();
	~zuMutalisk();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

