#pragma once
#include "Building.h"
class zbSpire : public Building
{
public:
	zbSpire();
	~zbSpire();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

