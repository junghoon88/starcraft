#pragma once
#include "gameNode.h"

class sceneMaptool : public gameNode
{
private:
public:
	sceneMaptool();
	~sceneMaptool();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);
};

