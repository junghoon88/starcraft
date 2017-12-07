#pragma once
#include "singletonBase.h"
#include "editbox.h"

class editboxManager : public singletonBase<editboxManager>
{
private:
	typedef map<wstring, editbox*> mapEditbox;
	typedef map<wstring, editbox*>::iterator mapEditboxIter;
	
private:
	mapEditbox _mapEditbox;

public:
	editboxManager();
	~editboxManager();

	HRESULT init(void);
	void release(void);

	editbox* addEditbox(wstring strKey, RECT rc);
	editbox* findEditbox(wstring strKey);
	void deleteEditbox(wstring strKey);

};

