#include "stdafx.h"
#include "sceneManager.h"
#include "DxWindow.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	sceneManager::_readyScene->init();

	sceneManager::_currentScene = sceneManager::_readyScene;
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

DxWindow* sceneManager::_currentScene = NULL;
DxWindow* sceneManager::_loadingScene = NULL;
DxWindow* sceneManager::_readyScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

void sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;
}

void sceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}


//�� �߰�
DxWindow* sceneManager::addScene(wstring sceneName, DxWindow* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

DxWindow* sceneManager::addLoadingScene(wstring loadingSceneName, DxWindow* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

bool sceneManager::isCurScene(wstring sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//�ش� ���� ã�� ���ߴٸ�         
	if (find == _mSceneList.end())    return false;

	//ã������ ���� ���� ���̸�
	if (find->second == _currentScene) return true;

	return false;
}


HRESULT sceneManager::changeScene(wstring sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//�ش� ���� ã�� ���ߴٸ�         �����߽��ϴ�!
	if (find == _mSceneList.end()) return E_FAIL;

	//ã������ ���� ���� ���� ���̸�	 �����ٰ� ���ض�
	if (find->second == _currentScene) return S_OK;

	//������ �ٲ�����
	find->second->init();
	if (_currentScene) _currentScene->release();
	_currentScene = find->second;

	return S_OK;
}

HRESULT sceneManager::changeScene(wstring sceneName, wstring loadingSceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (find == _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	find->second->init();
	if (_currentScene) _currentScene->release();
	_loadingScene = findLoading->second;
	_readyScene = find->second;
	CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));

	return S_OK;
}


