#pragma once
#include "gameObject.h"

class gameObjectPool
{
private:
	vector<gameObject*>		_vGameObjects;
	UINT					_poolSize;
	UINT					_nextAdress;


public:
	gameObjectPool();
	~gameObjectPool();

	void init(UINT poolSize);
	void release(void);
	gameObject* getNextAdress(void);
};

