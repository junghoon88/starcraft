#pragma once
#include "gameNode.h"
#include "tileNode.h"

class fog : public gameNode
{
public:
	fog();
	~fog();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};
