#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	:_system(NULL),
	_channel(NULL),
	_sound(NULL)
{
}


soundManager::~soundManager()
{

}

HRESULT soundManager::init(void)
{
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	return S_OK;
}

void soundManager::release(void)
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 닫기 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update(void)	
{
	//사운드 System 계속적으로 업데이트
	_system->update();

	//볼륨이 바뀌거나 
	//재생이 끝난 사운드를 채널에서 빼내는등의 다양한
	//작업을 자동으로 해준다
}


bool soundManager::addSound(wstring keyName, wstring soundName, bool bgm, bool loop)
{
	//soundName = L"Music/jaguar.wav";
	char* strSoundName = convert_mb(soundName);

	if (loop)
	{
		if (bgm)
		{
			_system->createStream(strSoundName, FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(strSoundName, FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(strSoundName, FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(strSoundName, FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}

	pair<arrSoundsIter, bool> result = _mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
	return result.second;
}

void soundManager::play(wstring keyName, float volume) 							  
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			Sound** ss = iter->second;
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[_mTotalChannels.size()]);
			//_system->playSound(_sound[count], 0, false, &_channel[count]); //1.10버전테스트
			//채널별로 볼륨 설정
			_channel[_mTotalChannels.size()]->setVolume(volume);

			_mTotalChannels.insert(make_pair(keyName, &_channel[_mTotalChannels.size()]));
			break;
		}
	}
}

void soundManager::stop(wstring keyName)											  
{
	arrChannelsIter iter = _mTotalChannels.begin();

	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->stop();
			iter = _mTotalChannels.erase(iter);
			break;
		}
	}
}

void soundManager::pause(wstring keyName)										  
{
	arrChannelsIter iter = _mTotalChannels.begin();

	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(wstring keyName)										  
{
	arrChannelsIter iter = _mTotalChannels.begin();

	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->setPaused(false);
			break;
		}
	}
}


bool soundManager::isPlaySound(wstring keyName) 
{
	bool isPlay = false;
	arrChannelsIter iter = _mTotalChannels.begin();

	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(wstring keyName)
{
	bool isPaused = false;
	arrChannelsIter iter = _mTotalChannels.begin();

	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getPaused(&isPaused);
			break;
		}
	}

	return isPaused;
}




Sound** soundManager::findSound(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			return iter->second;
		}
	}
	return NULL;
}

TCHAR* soundManager::getName(wstring keyName)
{
	TCHAR* name = L"";
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			Sound* sound = *iter->second;
			char cname[100];
			sound->getName(cname, 100);
			name = convert_wc(cname);

			
			//sound->getNumSubSounds(&numsubsound); //서브로 몇개 사운드 하고있는지??
			//sound->getNumTags(&numtag, &numtagsubdated); //??
			//sound->getTag(name, 0, &tag); //??



			printf("");


			break;
		}
	}
	return name;
}

unsigned int soundManager::getLength(wstring keyName)
{
	unsigned int length;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getLength(&length, FMOD_TIMEUNIT_MS);
			break;
		}
	}
	return length;
}

unsigned int soundManager::getPosition(wstring keyName)
{
	unsigned int position = 0;
	arrChannelsIter iter = _mTotalChannels.begin();
	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getPosition(&position, FMOD_TIMEUNIT_MS);
			break;
		}
	}
	return position;
}

void soundManager::setPosition(wstring keyName, unsigned int position)
{
	arrChannelsIter iter = _mTotalChannels.begin();
	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->setPosition(position, FMOD_TIMEUNIT_MS);
			break;
		}
	}
}

void soundManager::setVolume(float volume)
{
	arrChannelsIter iter = _mTotalChannels.begin();
	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		(*iter->second)->setVolume(volume);
	}
}

void soundManager::setMute(bool mute)
{
	arrChannelsIter iter = _mTotalChannels.begin();
	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		(*iter->second)->setMute(mute);
	}
}
bool soundManager::getMute(wstring keyName)
{
	bool mute = false;
	arrChannelsIter iter = _mTotalChannels.begin();
	for (iter; iter != _mTotalChannels.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getMute(&mute);
			break;
		}
	}
	return mute;
}

TCHAR* soundManager::getFormatType(wstring keyName)
{
	FMOD_SOUND_TYPE type = FMOD_SOUND_TYPE_UNKNOWN;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			Sound* sound = *iter->second;

			FMOD_SOUND_FORMAT format;
			int channel;
			int bit;
			sound->getFormat(&type, &format, &channel, &bit); //타입(MPEG), 포멧(16bit integer PCM data), 현재채널?, 16비트
			break;
		}
	}
	switch (type)
	{
		case FMOD_SOUND_TYPE_UNKNOWN:         /* 3rd party / unknown plugin format. */
			break;
		case FMOD_SOUND_TYPE_AIFF:            /* AIFF. */
			break;
		case FMOD_SOUND_TYPE_ASF:             /* Microsoft Advanced Systems Format (ie WMA/ASF/WMV). */
			break;
		case FMOD_SOUND_TYPE_AT3:             /* Sony ATRAC 3 format */
			break;
		case FMOD_SOUND_TYPE_CDDA:            /* Digital CD audio. */
			break;
		case FMOD_SOUND_TYPE_DLS:             /* Sound font / downloadable sound bank. */
			break;
		case FMOD_SOUND_TYPE_FLAC:            /* FLAC lossless codec. */
			break;
		case FMOD_SOUND_TYPE_FSB:             /* FMOD Sample Bank. */
			break;
		case FMOD_SOUND_TYPE_GCADPCM:         /* Nintendo GameCube/Wii ADPCM */
			break;
		case FMOD_SOUND_TYPE_IT:              /* Impulse Tracker. */
			break;
		case FMOD_SOUND_TYPE_MIDI:            /* MIDI. extracodecdata is a pointer to an FMOD_MIDI_EXTRACODECDATA structure. */
			break;
		case FMOD_SOUND_TYPE_MOD:             /* Protracker / Fasttracker MOD. */
			break;
		case FMOD_SOUND_TYPE_MPEG:            /* MP2/MP3 MPEG. */
			return L"MP3";
			break;
		case FMOD_SOUND_TYPE_OGGVORBIS:       /* Ogg vorbis. */
			return L"OGG";
			break;
		case FMOD_SOUND_TYPE_PLAYLIST:        /* Information only from ASX/PLS/M3U/WAX playlists */
			break;
		case FMOD_SOUND_TYPE_RAW:             /* Raw PCM data. */
			break;
		case FMOD_SOUND_TYPE_S3M:             /* ScreamTracker 3. */
			break;
		case FMOD_SOUND_TYPE_SF2:             /* Sound font 2 format. */
			break;
		case FMOD_SOUND_TYPE_USER:            /* User created sound. */
			break;
		case FMOD_SOUND_TYPE_WAV:             /* Microsoft WAV. */
			return L"WAV";
			break;
		case FMOD_SOUND_TYPE_XM:              /* FastTracker 2 XM. */
			break;
		case FMOD_SOUND_TYPE_XMA:             /* Xbox360 XMA */
			break;
		case FMOD_SOUND_TYPE_VAG:             /* PlayStation Portable ADPCM VAG format. */
			break;
		case FMOD_SOUND_TYPE_AUDIOQUEUE:      /* iPhone hardware decoder, supports AAC, ALAC and MP3. extracodecdata is a pointer to an FMOD_AUDIOQUEUE_EXTRACODECDATA structure. */
			break;
		case FMOD_SOUND_TYPE_XWMA:            /* Xbox360 XWMA */
			break;
		case FMOD_SOUND_TYPE_BCWAV:           /* 3DS BCWAV container format for DSP ADPCM and PCM */
			break;
		case FMOD_SOUND_TYPE_AT9:             /* NGP ATRAC 9 format */
			break;
		case FMOD_SOUND_TYPE_VORBIS:          /* Raw vorbis */
			break;
		case FMOD_SOUND_TYPE_MEDIA_FOUNDATION:/* Microsoft Media Foundation wrappers, supports ASF/WMA */
			break;
	}

	return L"";
}

void soundManager::delteSound(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); )
	{
		if (keyName == iter->first)
		{
			iter = _mTotalSounds.erase(iter);
		}
		else ++iter;
	}
}