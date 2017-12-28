#pragma once
#include "Building.h"
class zbQueensNest : public Building
{
public:
	zbQueensNest();
	~zbQueensNest();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

