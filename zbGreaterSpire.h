#pragma once
#include "Building.h"
class zbGreaterSpire : public Building
{
public:
	zbGreaterSpire();
	~zbGreaterSpire();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

