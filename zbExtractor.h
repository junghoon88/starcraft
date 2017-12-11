#pragma once
#include "Building.h"
class zbExtractor : public Building
{
public:
	zbExtractor();
	~zbExtractor();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

