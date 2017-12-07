#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class effect;

class effectManager : public singletonBase <effectManager>
{
private:
	//생산
	typedef vector<effect*> arrEffects;
	typedef vector<effect*>::iterator iterEffects;
	//가공
	typedef map<wstring, arrEffects> arrEffect;
	typedef map<wstring, arrEffects>::iterator iterEffect;
	//포장
	typedef vector<map<wstring, arrEffects>> arrTotalEffect;
	typedef vector<map<wstring, arrEffects>>::iterator iterTotalEffect;

private:
	arrTotalEffect _vTotalEffect;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addEffect(wstring effectName, const TCHAR* imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer);

	void play(wstring effectName, int x, int y);


	effectManager();
	~effectManager();
};

