//------------------------------------------------------------------------------------------
//
//  FontLibrary.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef FONTLIBRARY_H
#define FONTLIBRARY_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <map>

#include "Window.h"

namespace Framework
{
	class FontLibrary
	{

	private:

		static FontLibrary* sInstance;

		std::map < std::string, TTF_Font* > fonts;

		FontLibrary() {};

	public:

		static FontLibrary* instance(){
			if (sInstance == 0)
			{
				sInstance = new FontLibrary();
				return sInstance;
			}
			return sInstance;
		}

		void fwf_initialize();
		void fwf_destroy();
		bool fwf_loadFont(std::string fileName, std::string id, int size);
		void fwf_renderText(const char* renderingString, std::string fontID, SDL_Color textColor, int x, int y);

	};
}

#endif