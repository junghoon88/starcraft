#pragma once
#include "Building.h"
class zbHatchery : public Building
{
public:
	zbHatchery();
	~zbHatchery();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

