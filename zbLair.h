#pragma once
#include "Building.h"
class zbLair : public Building
{
public:
	zbLair();
	~zbLair();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

