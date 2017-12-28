#pragma once
#include "Building.h"
class zbUltraliskCavern : public Building
{
public:
	zbUltraliskCavern();
	~zbUltraliskCavern();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

};

