#include "stdafx.h"
#include "gameObjectPool.h"


gameObjectPool::gameObjectPool()
	: _poolSize(0), _nextAdress(0)
{
	_vGameObjects.clear();
}


gameObjectPool::~gameObjectPool()
{
}

void gameObjectPool::init(UINT poolSize)
{
	_poolSize = poolSize;

	//i++보다 ++i가 더 빠를 수 있다
	//objectPool방식이므로 최초에 최대 수량만큼 할당한다
	//이때, pushBack으로 벡터에 담는 것보다 index로 넣는 게 빠르므로 벡터 크기를 미리 잡는다

	_vGameObjects.resize(_poolSize);

	for (int i = 0; i < _poolSize; ++i)
	{
		gameObject* object = new gameObject();
		_vGameObjects[i] = object;
	}
}

void gameObjectPool::release(void)
{
	for (int i = 0; i < _poolSize; ++i)
	{
		SAFE_RELEASEDELETE(_vGameObjects[i]);
	}
	_vGameObjects.clear();
}

gameObject* gameObjectPool::getNextAdress(void)
{
	gameObject* object = NULL;

	for (int i = 0; i < _poolSize; ++i)
	{
		if (_vGameObjects[_nextAdress + i]->getValid() == false)
		{
			object = _vGameObjects[_nextAdress + i];
			_nextAdress = (_nextAdress + i + 1 ) >= _poolSize ? 0 : _nextAdress + i + 1;
			break;
		}
	}
	return object;
}


