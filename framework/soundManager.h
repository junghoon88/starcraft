#pragma once
#include "singletonBase.h"
#include <map>
#include <vector>

//#include "FMOD/inc/fmod.hpp"
#include "FMOD_old/inc/fmod.hpp"

//#pragma comment(lib, "FMOD/lib/fmod_vc.lib")
#pragma comment(lib, "FMOD_old/lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
	
private:
	typedef map<wstring, Sound**> arrSounds;
	typedef map<wstring, Sound**>::iterator arrSoundsIter;
	typedef map<wstring, Channel**> arrChannels;
	typedef map<wstring, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;
	arrChannels _mTotalChannels;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	bool addSound(wstring keyName, wstring soundName, bool bgm, bool loop);
	void play(wstring keyName, float volume = 1.0f); // 0.0 ~ 1.0f == 0 ~ 255
	void stop(wstring keyName);
	void pause(wstring keyName);
	void resume(wstring keyName);

	bool isPlaySound(wstring keyName);
	bool isPauseSound(wstring keyName);
	void setMuteAll(bool mute);
	bool getMute(wstring keyName);

	Sound** findSound(wstring keyName);

	TCHAR* getName(wstring keyName);
	unsigned int getLength(wstring keyName);
	unsigned int getPosition(wstring keyName);
	void setPosition(wstring keyName, unsigned int position);
	void setVolume(float volume);
	TCHAR* getFormatType(wstring keyName);
	void delteSound(wstring keyName);
	//TCHAR* getNumSubSounds(wstring keyName);


	soundManager();
	~soundManager();
};

