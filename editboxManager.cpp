#include "stdafx.h"
#include "editboxManager.h"


editboxManager::editboxManager()
{
}


editboxManager::~editboxManager()
{
}

HRESULT editboxManager::init(void)
{
	return S_OK;
}

void editboxManager::release(void)
{
	mapEditboxIter iter = _mapEditbox.begin();

	for (; iter != _mapEditbox.end(); )
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mapEditbox.erase(iter);
		}
		else ++iter;
	}

	_mapEditbox.clear();
}

editbox* editboxManager::addEditbox(wstring strKey, RECT rc)
{
	editbox* eb = findEditbox(strKey);

	if (eb) return eb;

	eb = new editbox;
	eb->init();
	eb->setRect(rc);

	_mapEditbox.insert(make_pair(strKey, eb));

	return NULL;
}

editbox* editboxManager::findEditbox(wstring strKey)
{
	mapEditboxIter iter = _mapEditbox.find(strKey);

	if (iter != _mapEditbox.end())
	{
		return iter->second;
	}

	return NULL;
}

void editboxManager::deleteEditbox(wstring strKey)
{
	mapEditboxIter iter = _mapEditbox.find(strKey);

	if (iter != _mapEditbox.end())
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mapEditbox.erase(iter);
		}
	}
}
