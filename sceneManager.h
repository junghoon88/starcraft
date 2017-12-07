#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<wstring, gameNode*> mapSceneList;
	typedef map<wstring, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;
	static gameNode* _loadingScene;
	static gameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;

	void playBGM(void);

public:
	sceneManager();
	~sceneManager();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);

	//¾À Ãß°¡
	gameNode* addScene(wstring sceneName, gameNode* scene);
	gameNode* addLoadingScene(wstring loadingSceneName, gameNode* scene);

	bool isCurScene(wstring sceneName);

	HRESULT changeScene(wstring sceneName);
	HRESULT changeScene(wstring sceneName, wstring loadingSceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);

};

