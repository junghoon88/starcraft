#include "stdafx.h"
#include "database.h"

database::database()
{
}


database::~database()
{

}

HRESULT database::init()
{
	//loadDatabase(L"database.txt");

	_stprintf(_strMapFile, L"");

	_gameStart = false;

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		_selectRaces[i] = RACES_ZERG;
	}

	_battleVictory = false;

	return S_OK;
}

void database::release()
{

}


void database::loadDatabase(wstring name)
{
	arrElements vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	wstring str;
	int count = 0;

	for (int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == L"|")
		{
			elements* em = new elements;
			str = vTemp[i + 1];

			_mTotalElement.insert(pair<wstring, elements*>(vTemp[i + 1], em));

			if (i != 0) count += 1;
			continue;
		}

		iterElement mIter = _mTotalElement.find(str);

		//mIter->second->character = (CHARACTER)_wtoi(vTemp[0].c_str());
	}

	vTemp.clear();
}


//������
void database::setElementDataCurrentHP(wstring str, float ch)
{
	iterElement mIter = _mTotalElement.find(str);
}
