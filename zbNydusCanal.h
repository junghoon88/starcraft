#pragma once
#include "Building.h"
class zbNydusCanal : public Building
{
public:
	zbNydusCanal();
	~zbNydusCanal();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

