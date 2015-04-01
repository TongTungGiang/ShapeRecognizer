//------------------------------------------------------------------------------------------
//
//  SoundManager.cpp
//
//  Created by CNTA.C++ Team in 2014
//
#include "SoundManager.h"

namespace Framework
{

	SoundManager* SoundManager::sInstance = NULL;

	SoundManager::SoundManager()
	{
		if (Mix_OpenAudio(22050, AUDIO_S16, 2, 4096) == -1)
			exit(EXIT_FAILURE);
	}

	SoundManager::~SoundManager()
	{
		Mix_CloseAudio();
	}

	bool SoundManager::load(std::string fileName, std::string id, sound_type type)
	{
		if (type == SOUND_MUSIC)
		{
			Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());

			if (pMusic == 0)
			{
				std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
				return false;
			}
			music[id] = pMusic;
			return true;
		}
		else if (type == SOUND_SFX)
		{
			Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
			if (pChunk == 0)
			{
				std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
				return false;
			}
			sfxs[id] = pChunk;
			return true;
		}
		return false;
	}

	void SoundManager::playMusic(std::string id, int loop)
	{
		Mix_PlayMusic(music[id], loop);
	}

	void SoundManager::playSound(std::string id, int loop)
	{
		Mix_PlayChannel(-1, sfxs[id], loop);
	}

}