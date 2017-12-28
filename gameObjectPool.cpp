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

	//i++���� ++i�� �� ���� �� �ִ�
	//objectPool����̹Ƿ� ���ʿ� �ִ� ������ŭ �Ҵ��Ѵ�
	//�̶�, pushBack���� ���Ϳ� ��� �ͺ��� index�� �ִ� �� �����Ƿ� ���� ũ�⸦ �̸� ��´�

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


