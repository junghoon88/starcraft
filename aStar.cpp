#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
	: _map(NULL)
{
}


aStar::~aStar()
{
	for (int i = 0; i < _vTotalList.size();)
	{
		if (_vTotalList[i] != NULL)
		{
			SAFE_RELEASEDELETE(_vTotalList[i]);
			_vTotalList.erase(_vTotalList.begin() + i);
		}
		else ++i;
	}

	_vTotalList.clear();	// 토탈 타일
	_vOpenList.clear();		// 갈 수 있는 타일
	_vCloseList.clear();	// 가장 가까운 타일
}

HRESULT aStar::init(void)
{
	//타일 셋팅
	initTiles();

	_findCnt = 0;
	_findCntMax = 100;

	return S_OK;
}

void aStar::initTiles(void)
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			tile* node = new tile;
			node->init(j, i, _map->getTiles()[j][i].rc);
			node->setAttribute(_map->getTiles()[j][i].attribute);
			node->setObject(_map->getTiles()[j][i].obj);

			_vTotalList.push_back(node);
		}
	}
}

//타일 셋팅할 함수
void aStar::setTiles(POINT startPt, POINT endPt)
{
	if (startPt.x == endPt.x && startPt.y == endPt.y)
	{
		_valid = false;
		return;
	}

	//startTile
	_staTile = _vTotalList[startPt.x + startPt.y * TILEX];

	//현재위치는 처음시작위치와 같도록함
	_curTile = _staTile;


	//endTile
	POINT index = endPt;
	
	tile* temp = _vTotalList[endPt.x + endPt.y * TILEX];
	while ((temp->getAttribute() & ATTR_UNMOVE) == ATTR_UNMOVE
			|| (temp->getAttribute() & ATTR_UNITSTOP) == ATTR_UNITSTOP
			|| temp->getObject() != OBJECT_NONE
			)
	{
		//움직일 수 없는 타일이거나 오브젝트가 있으면 인덱스를 수정한다.

		float angleDeg = getAngleDeg(startPt.x, startPt.y, index.x, index.y);
		if ((angleDeg >= 0 && angleDeg <= 45) || (angleDeg >= 315 && angleDeg < 360))
		{
			//오른쪽방향
			index.x--;
		}
		else if (angleDeg > 45 && angleDeg < 135)
		{
			//위쪽방향
			index.y++;
		}
		else if (angleDeg >= 135 && angleDeg <= 225)
		{
			//왼쪽방향
			index.x++;
		}
		else if (angleDeg > 225 && angleDeg < 315)
		{
			//아래방향
			index.y--;
		}

		//start 와 같아지면 취소
		if (index.x == startPt.x && index.y == startPt.y)
		{
			_valid = false;
			return;
		}

		temp = _vTotalList[index.x + index.y * TILEX];
	}
	_endTile = temp;

	_valid = true;
}

void aStar::updateMapInfo(void)
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		int idx = i % TILEX;
		int idy = i / TILEX;
		_vTotalList[i]->setAttribute(_map->getTiles()[idx][idy].attribute);
		_vTotalList[i]->setObject(_map->getTiles()[idx][idy].obj);
	}
}


//현재 타일에서 갈수 있는 길 찾는 함수
vector<tile*> aStar::addOpenList(tile* currentTile)
{
	//_curTile = currentTile;

	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; i++) //y
	{
		for (int j = 0; j < 3; j++) //x
		{
			if (i == 1 && j == 1) continue;
			if ((startX + j) < 0) continue;
			if ((startY + i) < 0) continue;
			if ((startX + j) > TILEX) continue;
			if ((startY + i) > TILEY) continue;


			tile* node = _vTotalList[((startY + i) * TILEX) + (startX + j)];

			if (!node->getIsOpen()) continue;
			if (node == _staTile) continue;
			if ((node->getAttribute() & ATTR_UNMOVE) == ATTR_UNMOVE) continue;
			if (node->getObject() != OBJECT_NONE) continue;

			if ((node->getAttribute() & ATTR_UNITSTOP) == ATTR_UNITSTOP) continue;

			node->setParentNode(currentTile);

			bool addObj = true;

			for (vTileIter _viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node != _endTile)
			{
				//node->setColor(RGB(128, 64, 28));
			}

			if (!addObj) continue;

			_vOpenList.push_back(node);
		}
	}

	if (_vOpenList.size() == 0)
	{
		printf("");
	}

	return _vOpenList;
}

//경로 탐색 함수
void aStar::pathFinder(tile* currentTile)
{
	if (!_valid)
		return;

	float tempTotalCost = 5000;
	tile* tempTile = NULL;

	int openListSize = addOpenList(currentTile).size();
	for (int i = 0; i < openListSize; i++)
	{
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		//POINT center2 = _vOpenList[i]->getCenter();
		//_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 14 : 10);
		_vOpenList[i]->setCostFromStart(10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (vTileIter _viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;

		_vOpenList.push_back(tempTile);
	}


	_findCnt++;
	if (_findCnt > _findCntMax)
	{
		while (tempTile->getParentNode() != NULL)
		{
			_vCloseList.push_back(tempTile);
			tempTile = tempTile->getParentNode();
		}

		return;
	}

	if (tempTile == _endTile)
	{
		while (tempTile->getParentNode() != NULL)
		{
			_vCloseList.push_back(tempTile);
			tempTile = tempTile->getParentNode();
		}

		return;
	}

	//_vCloseList.push_back(tempTile);

	for (vTileIter _viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	if (tempTile == NULL)
	{
		printf("");
		return;
	}
	_curTile = tempTile;

	//재귀함수
	pathFinder(_curTile);
}


void aStar::clearTiles(void)
{
	_vCloseList.clear();
	_vOpenList.clear();

	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->setParentNode(NULL);
		_vTotalList[i]->setIsOpen(true);
	}

	_findCnt = 0;
}



tile* aStar::getTile(POINT tilePt)
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		if (tilePt.x == _vTotalList[i]->getIdX() && tilePt.y == _vTotalList[i]->getIdY())
		{
			return _vTotalList[i];
		}
	}

	return NULL;
}