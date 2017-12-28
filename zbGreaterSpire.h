#pragma once
#include "Building.h"
class zbGreaterSpire : public Building
{
public:
	zbGreaterSpire();
	~zbGreaterSpire();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

