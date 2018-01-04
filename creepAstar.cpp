#include "stdafx.h"
#include "creepAstar.h"


creepAstar::creepAstar(gameMap* map)
	: _startTile(NULL), _nextTile(NULL)
{
	_map = map;

	_cost = 0;		//가로 : 13, 세로 : 16 소모 
	_costMax = 100; //가로로 8칸, 세로로 6.5칸
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

//타일 셋팅할 함수
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



//현재 타일에서 갈수 있는 길 찾는 함수
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

			if (node->getIsOpen()) continue; //이미 열었으면
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

			if (addObj == false) continue; //이미 벡터에 있으면 계속

			newOpenList.push_back(node);
		}
	}

	return newOpenList;
}


//경로 탐색 함수
//cost 가 같은 타일에서만 찾는다.
BOOL creepAstar::findCloseCreep(tile* currentTile, int cost)
{
	if (currentTile == NULL)
		return FALSE;

	//이미 find 했던 타일은 넘긴다.
	if (currentTile->getIsFind())
	{
		return FALSE;
	}

	//행동력이 최대를 넘어가면 찾지 않는다.
	if (currentTile->getTotalCost() >= _costMax)
	{
		return FALSE;
	}

	//시작 기준으로 퍼져나가도록 OpenTile 을 증가시킨다.
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

	//더이상 못찾았으면 끝낸다.
	if (newOpenList.size() == 0)
		return FALSE;


	for (int i = 0; i < newOpenList.size(); i++)
	{
		int width = abs(newOpenList[i]->getIdX() - _startTile->getIdX());
		int height = abs(newOpenList[i]->getIdY() - _startTile->getIdY());

		int curCost = sqrt(pow(width * 13, 2) + pow(height * 16, 2));


		newOpenList[i]->setTotalCost(curCost);
		newOpenList[i]->setIsOpen(true);

		//크립이 없으면!
		if ((newOpenList[i]->getAttribute() & ATTR_CREEP) == 0)
		{
			_nextTile = newOpenList[i];
			return TRUE;
		}

		//새로 찾은 OpenTile 을 맴버변수에 업데이트 해준다.
		_vOpenList.push_back(newOpenList[i]);
	}



	//재귀함수!!
	//현재 열려있는 타일을 기준으로 뻗어나간다.
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

	//이미 find 했던 타일은 넘긴다.
	if (currentTile->getIsFind())
	{
		return;
	}

	//행동력이 최대를 넘어가면 찾지 않는다.
	if (currentTile->getTotalCost() >= _costMax)
	{
		return;
	}

	//시작 기준으로 퍼져나가도록 OpenTile 을 증가시킨다.
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

	//더이상 못찾았으면 끝낸다.
	if (newOpenList.size() == 0)
		return;


	for (int i = 0; i < newOpenList.size(); i++)
	{
		int width  = abs(newOpenList[i]->getIdX() - _startTile->getIdX());
		int height = abs(newOpenList[i]->getIdY() - _startTile->getIdY());

		int curCost = sqrt(pow(width * 13, 2) + pow(height * 16, 2));


		newOpenList[i]->setTotalCost(curCost);
		newOpenList[i]->setIsOpen(true);

		//새로 찾은 OpenTile 을 맴버변수에 업데이트 해준다.
		_vOpenList.push_back(newOpenList[i]);
	}



	//재귀함수!!
	//현재 열려있는 타일을 기준으로 뻗어나간다.
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
