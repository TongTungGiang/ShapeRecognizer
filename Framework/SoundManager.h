//------------------------------------------------------------------------------------------
//
//  SoundManager.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL/SDL_mixer.h>
#include <map>
#include <string>
#include <iostream>

namespace Framework
{

	enum sound_type
	{
		SOUND_MUSIC,
		SOUND_SFX
	};

	class SoundManager
	{

	private:

		static SoundManager* sInstance;

		std::map < std::string, Mix_Chunk* > sfxs;
		std::map < std::string, Mix_Music* > music;

		SoundManager();
		~SoundManager();

		SoundManager(const SoundManager&);
		SoundManager &operator = (const SoundManager&);

	public:

		static SoundManager* Instance()
		{
			if (sInstance == 0)
			{
				sInstance = new SoundManager();
				return sInstance;
			}
			return sInstance;
		}

		bool load(std::string fileName, std::string id, sound_type type);

		void playSound(std::string id, int loop);
		void playMusic(std::string id, int loop);

	};

}

#endif