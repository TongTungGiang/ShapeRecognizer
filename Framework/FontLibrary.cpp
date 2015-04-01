//------------------------------------------------------------------------------------------
//
//  FontLibrary.cpp
//
//  Created by CNTA.C++ Team in 2014
//
#include "FontLibrary.h"
#include <iostream>

namespace Framework
{
	FontLibrary* FontLibrary::sInstance = NULL;

	void FontLibrary::fwf_initialize()
	{
		if (TTF_Init() == -1)
		{
			std::cout << " Failed to initialize SDL_TTF : " << TTF_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	void FontLibrary::fwf_destroy()
	{
		TTF_Quit();
	}

	bool FontLibrary::fwf_loadFont(std::string fileName, std::string id, int size)
	{
		TTF_Font* temp = TTF_OpenFont(fileName.c_str(), size);

		if (temp == 0)
		{
			//std::cout << " Failed to load font : " << fileName << std::endl;
			return false;
		}
		fonts[id] = temp;
		return true;
	}

	void FontLibrary::fwf_renderText(const char* renderingString, std::string fontID, SDL_Color textColor, int x, int y)
	{
		SDL_Surface *textSurface = TTF_RenderText_Solid(fonts[fontID], renderingString, textColor);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Window::instance()->fww_getWindowRenderer(), textSurface);
		SDL_FreeSurface(textSurface);

		SDL_Rect textRect;
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		textRect.x = x;
		textRect.y = Window::instance()->fww_getHeight() - y - textRect.h;

		SDL_RenderCopy(Window::instance()->fww_getWindowRenderer(), textTexture, NULL, &textRect);

		SDL_DestroyTexture(textTexture);
	}
}