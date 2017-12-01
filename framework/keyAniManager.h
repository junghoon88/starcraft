#pragma once
#include "singletonBase.h"
#include <map>
#include <vector>

class image;
class animation;

class keyAniManager : public singletonBase<keyAniManager>
{
private:
	typedef map<wstring, animation*> arrAnimation;
	typedef map<wstring, animation*>::iterator iterAnimations;
	typedef vector<arrAnimation> vArrAnimation;
	typedef vector<arrAnimation>::iterator viArrAnimation;

private:
	vArrAnimation _vTotalAnimation;
	//arrAnimation _mTotalAnimation;

public:
	keyAniManager();
	~keyAniManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//����Ʈ Ű �ִϸ��̼�
	void addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop);
	void addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction);
	void addDefaultFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	//�迭 Ű �ִϸ��̼�
	void addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop);
	void addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction);
	void addArrayFrameAnimation(wstring animationKeyName, const TCHAR* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj);

	//���� Ű �ִϸ��̼�
	void addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction);
	void addCoordinateFrameAnimation(wstring animationKeyName, TCHAR* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	void start(wstring animationKeyName);
	void stop(wstring animationKeyName);
	void pause(wstring animationKeyName);
	void resume(wstring animationKeyName);

	animation* findAnimation(wstring animationKeyName);

	void deleteAll();

};

