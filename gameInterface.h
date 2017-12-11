#pragma once
#include "gameNode.h"
class gameInterface : public gameNode
{
private:
	image*		_imgInterface;



public:
	gameInterface();
	~gameInterface();


	HRESULT init(RACES race);
	void release(void);
	void update(void);
	void render(void);
};

