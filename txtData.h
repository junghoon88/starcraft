#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

class txtData : public singletonBase<txtData>
{
public:
	HRESULT init();
	void release();

	//���̺�
	void txtSave(const TCHAR* saveFileName, vector<wstring> vStr);
	TCHAR* vectorArrayCombine(vector<wstring> vArray);

	//�ε�
	vector<wstring> txtLoad(const TCHAR* loadFileName);
	vector<wstring> charArraySeparation(TCHAR charArray[]);

	txtData();
	~txtData();
};

