#pragma once
#include "Building.h"
class zbLair : public Building
{
private:
	vector<zuLarva*>	_vLarva;

public:
	zbLair();
	~zbLair();

	HRESULT init(POINT ptTIle);
	void release(void);
	void update(void);
	void render(void);

public:
	vector<zuLarva*> getLarvas(void) { return _vLarva; }

};

