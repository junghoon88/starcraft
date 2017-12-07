#pragma once
#include "singletonBase.h"
#include <vector>

struct tagIniData
{
	const TCHAR* subject;		//�׸�			���
	const TCHAR* title;			//������			����
	const TCHAR* body;			//��(value)		99
};

class iniDataManager : public singletonBase<iniDataManager>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<tagIniData>::iterator arrIniDataIter;

	typedef vector<arrIniData> arrIniDatas;
	typedef vector<arrIniData>::iterator arrIniDatasIter;

private:
	arrIniDatas _vIniData;
	
public:
	HRESULT init();
	void release();

	void addData(const TCHAR* subject, const TCHAR* title, const TCHAR* body);
	void iniSave(TCHAR* fileName);

	TCHAR* loadDataString(const TCHAR* fileName, const TCHAR* subject, const TCHAR* title);
	int loadDataInterger(const TCHAR* fileName, const TCHAR* subject, const TCHAR* title);


	iniDataManager();
	~iniDataManager();
};

