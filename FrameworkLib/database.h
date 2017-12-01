#pragma once
#include "singletonBase.h"

class elements
{
public:


	elements() {};
	~elements() {};
};

class database : public singletonBase<database>
{
private:
	typedef vector<wstring> arrElements;
	typedef vector<wstring>::iterator iterElements;

	typedef map<wstring, elements*> arrElement;
	typedef map<wstring, elements*>::iterator iterElement;

	arrElement _mTotalElement;

public:
	database();
	~database();

	void init();
	void release();

	//void loadDatabase(wstring name);

	//속성에 대한 접근자
	elements* getElementData(wstring str) { return _mTotalElement.find(str)->second; }
};

