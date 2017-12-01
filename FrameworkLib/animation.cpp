#include "stdafx.h"
#include "animation.h"

animation::animation()
	: _frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIndex(0),
	_play(FALSE)

{
}


animation::~animation()
{
}

//                          300         300         30           30
HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	_frameNum = _frameNumWidth * _frameNumHeight;

	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;

			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	setDefPlayFrame();

	return S_OK;
}

void animation::release(void)										   
{

}


void animation::setDefPlayFrame(BOOL reverse, BOOL loop)				 
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	//0, 1, 2, 3, 4, 5
	for (int i = 0; i < _frameNum; i++)
	{
		_playList.push_back(i);
	}
	if (reverse)
	{
		//4, 3, 2, 1
		for (int i = _frameNum - 1; i > 0; i--)
		{
			_playList.push_back(i);
		}
	}

}
void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNC cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	//0, 1, 2, 3, 4, 5
	for (int i = 0; i < _frameNum; i++)
	{
		_playList.push_back(i);
	}
	if (reverse)
	{
		//4, 3, 2, 1
		for (int i = _frameNum - 1; i > 0; i--)
		{
			_playList.push_back(i);
		}
	}

}
void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;

	_playList.clear();

	//0, 1, 2, 3, 4, 5
	for (int i = 0; i < _frameNum; i++)
	{
		_playList.push_back(i);
	}
	if (reverse)
	{
		//4, 3, 2, 1
		for (int i = _frameNum - 1; i > 0; i--)
		{
			_playList.push_back(i);
		}
	}

}


//배열에 담아서 애니메이션 재생
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)		 
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNC cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

//시작과 끝 구간이 있는 애니메이션
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();
	//만약 시작과 끝 번호가 같다면
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}
	
	if (start > end)
	{
		//만약 start=5, end=2 라면 5, 4, 3, 2
		for (int i = start; i >= end; i--)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//3, 4 
			for (int i = end + 1; i < start; i++)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//만약 start=2, end=5 라면 2, 3, 4, 5
		for (int i = start; i <= end; i++)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//4, 3
			for (int i = end - 1; i > start; i--)
			{
				_playList.push_back(i);
			}
		}
	}

}
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNC cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();
	//만약 시작과 끝 번호가 같다면
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}

	if (start > end)
	{
		//만약 start=5, end=2 라면 5, 4, 3, 2
		for (int i = start; i >= end; i--)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//3, 4 
			for (int i = end + 1; i < start; i++)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//만약 start=2, end=5 라면 2, 3, 4, 5
		for (int i = start; i <= end; i++)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//4, 3
			for (int i = end - 1; i > start; i--)
			{
				_playList.push_back(i);
			}
		}
	}

}
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNC_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;

	_playList.clear();
	//만약 시작과 끝 번호가 같다면
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}

	if (start > end)
	{
		//만약 start=5, end=2 라면 5, 4, 3, 2
		for (int i = start; i >= end; i--)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//3, 4 
			for (int i = end + 1; i < start; i++)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//만약 start=2, end=5 라면 2, 3, 4, 5
		for (int i = start; i <= end; i++)
		{
			_playList.push_back(i);
		}
		if (reverse)
		{
			//4, 3
			for (int i = end - 1; i > start; i--)
			{
				_playList.push_back(i);
			}
		}
	}

}


void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}


void animation::frameUpdate(float elapsedTime)
{
	if (_play)
	{
		_elapsedSec += elapsedTime;

		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIndex++;

			if (_nowPlayIndex == _playList.size())
			{
				if (_loop) _nowPlayIndex = 0;
				else
				{
					if (_obj == NULL)
					{
						if (_callbackFunction != NULL) _callbackFunction();
					}
					else
					{
						_callbackFunctionParameter(_obj);
					}

					_nowPlayIndex--;
					_play = FALSE;
				}
			}
		}
	}
}


void animation::start(void)	
{
	_play = TRUE;
	_nowPlayIndex = 0;
}

void animation::stop(void)	
{
	_play = FALSE;
	_nowPlayIndex = 0;
}

void animation::pause(void)	
{
	_play = FALSE;
}

void animation::resume(void)
{
	_play = TRUE;
}
