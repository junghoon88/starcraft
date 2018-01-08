#include "stdafx.h"
#include "creepManager.h"


creepManager::creepManager()
	: _aStar(NULL)
{
}


creepManager::~creepManager()
{
	_vCreeps.clear();
}

void creepManager::init(gameMap* map)
{
	_gameMap = map;

	_aStar = new creepAstar(map);
	_aStar->initTiles();
}

void creepManager::update(void)
{
	updateSpread();
	updateDisappear();
}

void creepManager::updateSpread(void)
{
	for (int i = 0; i < _vCreeps.size(); i++)
	{
		if (_vCreeps[i].isSpreading == FALSE) continue;

		_aStar->clearTiles();
		_aStar->updateTileAttr();	//속성값 업데이트
		_aStar->setTiles(_vCreeps[i].pt);
		tile* start = _aStar->findTile(_vCreeps[i].pt);
		if (start != NULL)
		{
			bool res = _aStar->findCloseCreep(start);
			if (res)
			{
				tile* next = _aStar->getNextTile();
				_gameMap->getTiles()[next->getIdX()][next->getIdY()].attribute |= ATTR_CREEP;
			}
			else
			{
				//더이상 못찾으면 퍼지지 않도록 한다.
				_vCreeps[i].isSpreading = FALSE;
			}
		}
	}

}
void creepManager::updateDisappear(void)
{
	for (int i = 0; i < _vCreeps.size(); i++)
	{
		if (_vCreeps[i].isDisappearing == FALSE) continue;

		bool erase = false;


		_aStar->clearTiles();
		_aStar->updateTileAttr();	//속성값 업데이트
		_aStar->setTiles(_vCreeps[i].pt);
		tile* start = _aStar->findTile(_vCreeps[i].pt);
		if (start != NULL)
		{
			_aStar->findCreepList(start);
			tile* next = _aStar->findFarCreep();

			if (next != NULL)
			{
				tile* next = _aStar->getNextTile();
				_gameMap->getTiles()[next->getIdX()][next->getIdY()].attribute &= ~ATTR_CREEP;
			}
			else
			{
				//더이상 못찾으면 벡터에서지운다.
				_vCreeps[i].isSpreading = FALSE;
				_vCreeps.erase(_vCreeps.begin() + i);
				i--;
			}
		}
	}
}


tagCreep* creepManager::findCreep(POINT pt)
{
	for (int i = 0; i < _vCreeps.size(); i++)
	{
		if (pt.x == _vCreeps[i].pt.x && pt.y == _vCreeps[i].pt.y)
		{
			return &_vCreeps[i];
		}
	}

	return NULL;
}


void creepManager::addCreep(POINT ptTile, POINT size)
{

	for (int i = -2; i < size.x + 2; i++)
	{
		for (int j = -2; j < size.y + 2; j++)
		{
			int idx = ptTile.x + i;
			int idy = ptTile.y + j;

			if (idx <= 0)		continue;
			if (idx >= TILEX)	continue;
			if (idy <= 0)		continue;
			if (idy >= TILEX)	continue;

			_gameMap->getTiles()[idx][idy].attribute |= ATTR_CREEP;
		}
	}


	POINT pt;
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			if (i > 0 && i < size.x - 1) continue;
			if (j > 0 && j < size.y - 1) continue;


			pt.x = ptTile.x + i;
			pt.y = ptTile.y + j;

			if (findCreep(pt) == NULL)
			{
				tagCreep creep;
				creep.pt = pt;
				creep.isSpreading = true;
				creep.isDisappearing = false;

				_vCreeps.push_back(creep);
			}
		}
	}
}

void creepManager::deleteCreep(POINT ptTile, POINT size)
{
	POINT pt;
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			if (i > 0 && i < size.x - 1) continue;
			if (j > 0 && j < size.y - 1) continue;

			pt.x = ptTile.x + i;
			pt.y = ptTile.y + j;

			tagCreep* creep = findCreep(pt);
			if (creep != NULL)
			{
				creep->isSpreading = false;
				creep->isDisappearing = true;
			}
		}
	}

}
