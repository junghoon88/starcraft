#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class DxWindow;
class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<wstring, DxWindow*> mapSceneList;
	typedef map<wstring, DxWindow*>::iterator mapSceneIter;

private:
	static DxWindow* _currentScene;
	static DxWindow* _loadingScene;
	static DxWindow* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;

public:
	sceneManager();
	~sceneManager();

	void init(void);
	void release(void);
	void update(void);
	void render(void);

	//¾À Ãß°¡
	DxWindow* addScene(wstring sceneName, DxWindow* scene);
	DxWindow* addLoadingScene(wstring loadingSceneName, DxWindow* scene);

	bool isCurScene(wstring sceneName);

	HRESULT changeScene(wstring sceneName);
	HRESULT changeScene(wstring sceneName, wstring loadingSceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

