#pragma once
#include "Building.h"
class zbHive : public Building
{
public:
	zbHive();
	~zbHive();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

