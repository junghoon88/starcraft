#pragma once
#include "Building.h"
class zbDefilerMound : public Building
{
public:
	zbDefilerMound();
	~zbDefilerMound();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

