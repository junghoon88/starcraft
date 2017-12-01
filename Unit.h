#pragma once
#include "DxWindow.h"

class Unit : public DxWindow
{
public:
	Unit();
	~Unit();

	void init(void);
	void release(void);
	void update(void);
	void render(void);

public:


};

