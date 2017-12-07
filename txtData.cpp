#include "stdafx.h"
#include "txtData.h"

txtData::txtData()
{
}


txtData::~txtData()
{

}

HRESULT txtData::init()
{

	return S_OK;
}

void txtData::release()
{

}


//세이브
void txtData::txtSave(const TCHAR* saveFileName, vector<wstring> vStr)
{
	HANDLE hFile;
	DWORD write;

	TCHAR str[512];
	ZeroMemory(str, sizeof(str));

	_tcsncpy_s(str, 512, vectorArrayCombine(vStr), 510);

	hFile = CreateFile(saveFileName, GENERIC_WRITE, FALSE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(hFile, str, (_tcslen(str) + 1) * sizeof(TCHAR), &write, NULL);

	CloseHandle(hFile);
}

TCHAR* txtData::vectorArrayCombine(vector<wstring> vArray)			
{
	TCHAR str[512];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		//100,100,100,100
		_tcsncat_s(str, 512, vArray[i].c_str(), 510);
		if (i + 1 < vArray.size()) _tcscat(str, L",");
	}

	return str;
}


//로드
vector<wstring> txtData::txtLoad(const TCHAR* loadFileName)
{
	HANDLE file;

	TCHAR str[512];
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 512, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<wstring> txtData::charArraySeparation(TCHAR charArray[])
{
	vector<wstring> vArray;

	TCHAR* separator = L",";
	TCHAR* token;

	token = _tcstok(charArray, separator);

	vArray.push_back(token);

	while (NULL != (token = _tcstok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
