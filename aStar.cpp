#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
	: _map(NULL)
{
}


aStar::~aStar()
{
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
			//DWORD attr = _map->getAttribute()[i * TILEX + j];
			//if ((attr & ATTR_UNMOVE) == ATTR_UNMOVE)
			//{
			//	node->setAttribute(L"unmove");
			//}

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

	bool staCheck = false;
	bool endCheck = false;

	for (int i = 0; i < _vTotalList.size(); i++)
	{
		POINT pt;
		pt.x = _vTotalList[i]->getIdX();
		pt.y = _vTotalList[i]->getIdY();

		if (pt.x == startPt.x && pt.y == startPt.y)
		{
			_staTile = _vTotalList[i];
			_staTile->setAttribute(L"start");
			staCheck = true;
		}
		else if (pt.x == endPt.x && pt.y == endPt.y)
		{
			_endTile = _vTotalList[i];
			_endTile->setAttribute(L"end");
			endCheck = true;
		}

		if (staCheck && endCheck)
			break;
	}
	_valid = true;
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
			if (node->getAttribute() == L"start") continue;
			if (node->getAttribute() == L"unmove") continue;

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

			if (node->getAttribute() != L"end")
			{
				//node->setColor(RGB(128, 64, 28));
			}

			if (!addObj) continue;

			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

//경로 탐색 함수
void aStar::pathFinder(tile* currentTile)
{
	if (!_valid)
		return;

	float tempTotalCost = 5000;
	tile* tempTile;

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

	_vCloseList.push_back(tempTile);

	_findCnt++;
	if (_findCnt > _findCntMax)
	{
		return;
	}

	if (tempTile == _endTile) //(tempTile->getAttribute() == L"end")
	{
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

	_curTile = tempTile;

	//재귀함수
	pathFinder(_curTile);
}

void aStar::release(void)
{

}

void aStar::update(void)
{

}

void aStar::render(void)
{

}

void aStar::clearTiles(void)
{
	_vCloseList.clear();
	_vOpenList.clear();

	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->setIsOpen(true);
		if (_vTotalList[i]->getAttribute() == L"start")
		{
			_vTotalList[i]->setAttribute(L"");
		}
		if (_vTotalList[i]->getAttribute() == L"end")
		{
			_vTotalList[i]->setAttribute(L"");
		}
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