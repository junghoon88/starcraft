#pragma once
#include "DxWindow.h"

class Building : public DxWindow
{
public:
	Building();
	~Building();

	void init(void);
	void release(void);
	void update(void);
	void render(void);

public:

};

