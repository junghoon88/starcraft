#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{

}


HRESULT iniDataManager::init()
{

	return S_OK;
}

void iniDataManager::release()
{

}


void iniDataManager::addData(const TCHAR* subject, const TCHAR* title, const TCHAR* body)
{
	tagIniData iniData;
	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);

}

void iniDataManager::iniSave(TCHAR* fileName)										  
{
	TCHAR str[256];
	TCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	_stprintf(dir, L"\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	_tcsncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}


	_vIniData.clear();
}


TCHAR* iniDataManager::loadDataString(const TCHAR* fileName, const TCHAR* subject, const TCHAR* title)
{
	TCHAR str[256];
	TCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	_stprintf(dir, L"\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	_tcsncat_s(str, 256, dir, 254);

	TCHAR data[65] = { NULL };
	GetPrivateProfileString(subject, title, L"", data, 64, str);

	return data;
}

int iniDataManager::loadDataInterger(const TCHAR* fileName, const TCHAR* subject, const TCHAR* title)
{
	TCHAR str[256];
	TCHAR dir[256];

	ZeroMemory(dir, sizeof(dir));
	_stprintf(dir, L"\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	_tcsncat_s(str, 256, dir, 254);


	return GetPrivateProfileInt(subject, title, 0, str);
}

