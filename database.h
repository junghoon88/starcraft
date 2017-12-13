#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class elements
{
public:


	elements(){};
	~elements(){};
};

class database : public singletonBase<database>
{
private:
	typedef vector<wstring> arrElements;
	typedef vector<wstring>::iterator iterElements;

	typedef map<wstring, elements*> arrElement;
	typedef map<wstring, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;

	int _mapNum;

	//플레이어가 선택한 종족 정보
	RACES	_selectRaces[PLAYER_NUM];

	bool _battleVictory;


public:
	HRESULT init();
	void release();

	void loadDatabase(wstring name);

	//속성에 대한 접근자
	elements* getElementData(wstring str) { return _mTotalElement.find(str)->second; }

	//설정자
	void setElementDataCurrentHP(wstring str, float ch);


	database();
	~database();

public:
	inline int getMapNum(void) { return _mapNum; }
	inline void setMapNum(int num) { _mapNum = num; }

	inline RACES getSelectRaces(PLAYER playerNum) { return _selectRaces[playerNum]; }

	inline bool getBattleVictory(void) { return _battleVictory; }
	inline void setBattleVictory(bool victory) { _battleVictory = victory; }


};

