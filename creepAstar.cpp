#include "stdafx.h"
#include "creepAstar.h"


creepAstar::creepAstar(gameMap* map)
	: _startTile(NULL), _nextTile(NULL)
{
	_map = map;

	_cost = 0;		//���� : 13, ���� : 16 �Ҹ� 
	_costMax = 100; //���η� 8ĭ, ���η� 6.5ĭ
}


creepAstar::~creepAstar()
{
	vTileIter iter = _vTotalList.begin();
	for (; iter != _vTotalList.end();)
	{
		if ((*iter) != NULL)
		{
			SAFE_RELEASEDELETE((*iter));
		}
		else ++iter;
	}
	_vTotalList.clear();
}

void creepAstar::initTiles(void)
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			tile* node = new tile;
			node->init(j, i, _map->getTiles()[j][i].rc);
			node->setAttribute(_map->getTiles()[j][i].attribute);

			_vTotalList.push_back(node);
		}
	}
}

void creepAstar::updateTileAttr(void)
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		int idx = i % TILEX;
		int idy = i / TILEX;
		_vTotalList[i]->setAttribute(_map->getTiles()[idx][idy].attribute);
	}
}

//Ÿ�� ������ �Լ�
void creepAstar::setTiles(POINT startPt)
{
	bool staCheck = false;


	int index = startPt.x + startPt.y * TILEX;

	_startTile = _vTotalList[index];
}

void creepAstar::clearTiles(void)
{
	_startTile = NULL;
	_nextTile = NULL;
	_vOpenList.clear();

	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->setIsOpen(false);
		_vTotalList[i]->setIsFind(false);
		_vTotalList[i]->setTotalCost(0);
	}

	_cost = 0;
}



//���� Ÿ�Ͽ��� ���� �ִ� �� ã�� �Լ�
vector<tile*> creepAstar::addOpenList(tile* currentTile, bool creepCheck)
{
	vector<tile*> newOpenList;
	newOpenList.clear();

	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; i++) //y
	{
		for (int j = 0; j < 3; j++) //x
		{
			if (i == 0 && j == 0) continue;
			if (i == 0 && j == 2) continue;
			//if (i == 1 && j == 1) continue;
			if (i == 2 && j == 0) continue;
			if (i == 2 && j == 2) continue;

			int targetX = startX + j;
			int targetY = startY + i;

			if (targetX < 0) continue;
			if (targetX >= TILEX) continue;
			if (targetY < 0) continue;
			if (targetY >= TILEY) continue;


			tile* node = findTile(targetX, targetY);
			if (node == NULL) continue;

			if (node->getIsOpen()) continue; //�̹� ��������
			if (node == _startTile) continue;
			if (node->getAttribute() & ATTR_UNBUILD) continue;

			if (creepCheck)
			{
				if ((node->getAttribute() & ATTR_CREEP) == 0) continue;
			}

			bool addObj = true;

			for (int i = 0; i < _vOpenList.size(); ++i)
			{
				if (node == _vOpenList[i])
				{
					addObj = false;
					break;
				}
			}

			if (addObj == false) continue; //�̹� ���Ϳ� ������ ���

			newOpenList.push_back(node);
		}
	}

	return newOpenList;
}


//��� Ž�� �Լ�
//cost �� ���� Ÿ�Ͽ����� ã�´�.
BOOL creepAstar::findCloseCreep(tile* currentTile, int cost)
{
	if (currentTile == NULL)
		return FALSE;

	//�̹� find �ߴ� Ÿ���� �ѱ��.
	if (currentTile->getIsFind())
	{
		return FALSE;
	}

	//�ൿ���� �ִ븦 �Ѿ�� ã�� �ʴ´�.
	if (currentTile->getTotalCost() >= _costMax)
	{
		return FALSE;
	}

	//���� �������� ������������ OpenTile �� ������Ų��.
	vector<tile*> newOpenList;
	if (currentTile->getTotalCost() == 0)
	{
		newOpenList = addOpenList(currentTile);
		currentTile->setIsFind(true);
	}
	else if (currentTile->getTotalCost() == cost)
	{
		newOpenList = addOpenList(currentTile);
		currentTile->setIsFind(true);
	}
	else
	{
		return FALSE;
	}

	//���̻� ��ã������ ������.
	if (newOpenList.size() == 0)
		return FALSE;


	for (int i = 0; i < newOpenList.size(); i++)
	{
		int width = abs(newOpenList[i]->getIdX() - _startTile->getIdX());
		int height = abs(newOpenList[i]->getIdY() - _startTile->getIdY());

		int curCost = sqrt(pow(width * 13, 2) + pow(height * 16, 2));


		newOpenList[i]->setTotalCost(curCost);
		newOpenList[i]->setIsOpen(true);

		//ũ���� ������!
		if ((newOpenList[i]->getAttribute() & ATTR_CREEP) == 0)
		{
			_nextTile = newOpenList[i];
			return TRUE;
		}

		//���� ã�� OpenTile �� �ɹ������� ������Ʈ ���ش�.
		_vOpenList.push_back(newOpenList[i]);
	}



	//����Լ�!!
	//���� �����ִ� Ÿ���� �������� �������.
	while (_cost < _costMax)
	{
		for (int i = 0; i < _vOpenList.size(); i++)
		{
			if (findCloseCreep(_vOpenList[i], _cost))
			{
				return TRUE;
			}
		}
		_cost++;
	}

	return FALSE;
}

void creepAstar::findCreepList(tile* currentTile, int cost)
{
	if (currentTile == NULL)
		return;

	//�̹� find �ߴ� Ÿ���� �ѱ��.
	if (currentTile->getIsFind())
	{
		return;
	}

	//�ൿ���� �ִ븦 �Ѿ�� ã�� �ʴ´�.
	if (currentTile->getTotalCost() >= _costMax)
	{
		return;
	}

	//���� �������� ������������ OpenTile �� ������Ų��.
	vector<tile*> newOpenList;
	if (currentTile->getTotalCost() == 0)
	{
		newOpenList = addOpenList(currentTile, true);
		currentTile->setIsFind(true);
	}
	else if (currentTile->getTotalCost() == cost)
	{
		newOpenList = addOpenList(currentTile, true);
		currentTile->setIsFind(true);
	}
	else
	{
		return;
	}

	//���̻� ��ã������ ������.
	if (newOpenList.size() == 0)
		return;


	for (int i = 0; i < newOpenList.size(); i++)
	{
		int width  = abs(newOpenList[i]->getIdX() - _startTile->getIdX());
		int height = abs(newOpenList[i]->getIdY() - _startTile->getIdY());

		int curCost = sqrt(pow(width * 13, 2) + pow(height * 16, 2));


		newOpenList[i]->setTotalCost(curCost);
		newOpenList[i]->setIsOpen(true);

		//���� ã�� OpenTile �� �ɹ������� ������Ʈ ���ش�.
		_vOpenList.push_back(newOpenList[i]);
	}



	//����Լ�!!
	//���� �����ִ� Ÿ���� �������� �������.
	while (_cost < _costMax)
	{
		for (int i = 0; i < _vOpenList.size(); i++)
		{
			findCreepList(_vOpenList[i], _cost);
		}
		_cost++;
	}

	return;
}

tile* creepAstar::findFarCreep(void)
{
	if (_vOpenList.size() == 0)
		return NULL;

	int index = 0;
	int maxCost = -1;

	for (int i = _vOpenList.size() - 1; i <= 0; i--)
	{
		if (maxCost < _vOpenList[i]->getTotalCost())
		{
			index = i;
			maxCost = _vOpenList[i]->getTotalCost();
		}
	}

	return _vOpenList[index];
}
