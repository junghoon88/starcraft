#pragma once
#include "Building.h"
class zbHive : public Building
{
private:
	vector<zuLarva*>	_vLarva;

public:
	zbHive();
	~zbHive();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

public:
	vector<zuLarva*> getLarvas(void) { return _vLarva; }

};

