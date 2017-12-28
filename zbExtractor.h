#pragma once
#include "Building.h"
class zbExtractor : public Building
{
public:
	zbExtractor();
	~zbExtractor();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

