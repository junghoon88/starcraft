#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{
}

void timeManager::init(void)
{
	_timer = new timer;
	_timer->init();
}

void timeManager::release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

void timeManager::render(void)
{
	TCHAR str[256];
	wstring frameRate;
	//SetBkMode(hdc, TRANSPARENT);

	//#include <assert.h>
	//assert(_viBullet->false, "여기에요 여기");
	//assert(false공식, "유언");

#ifdef _DEBUG
	{
		//wsprintf(str, L"framePerSec(FPS) : %d", _timer->getFrameRate());
		//TextOut(hdc, 0, 0, str, _tcslen(str));

		//_stprintf_s(str, L"worldTime : %f", _timer->getWorldTime());
		//TextOut(hdc, 0, 20, str, _tcslen(str));

		//_stprintf_s(str, L"elapsedTime : %f", _timer->getElapsedTime());
		//TextOut(hdc, 0, 40, str, _tcslen(str));
	}
#else
	{
		//wsprintf(str, L"framePerSec(FPS) : %d", _timer->getFrameRate());
		//TextOut(hdc, 0, 0, str, _tcslen(str));
	}
#endif
}
