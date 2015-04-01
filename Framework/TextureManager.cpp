//------------------------------------------------------------------------------------------
//
//  TextureManager.cpp
//
//  Created by CNTA.C++ Team in 2014
//
#include "TextureManager.h"
#include <iostream>

namespace Framework
{

	unsigned int TextureManager::iterator_texture = 0;
	std::vector<fw_Texture*>* TextureManager::textureArray = NULL;
	TextureManager* TextureManager::singleton = NULL;

	void TextureManager::fwtm_initialize()
	{
		singleton = NULL;
		iterator_texture = 0;
		textureArray = new std::vector<fw_Texture*>;
	}

	unsigned int TextureManager::fwtm_createTextureFromFile(std::string filename)
	{
		SDL_Surface* newSurface = IMG_Load(filename.c_str());
		if (newSurface == NULL)
			std::cout << "Cannot load the file at " << filename << std::endl;
		SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Window::instance()->fww_getWindowRenderer(), newSurface);
		if (newTexture == NULL)
			std::cout << "CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(newSurface);
		textureArray->push_back(newTexture);
		iterator_texture++;
		return (iterator_texture - 1);
	}

	fw_Texture* TextureManager::fwtm_createTempTextureFromFile(std::wstring filename)
	{
		char* buffer = new char[255];
		size_t charsConverted = 0;
		wcstombs_s(&charsConverted, buffer, (size_t)(filename.length() + 1), filename.c_str(), filename.length());

		SDL_Surface* newSurface = IMG_Load(buffer);
		delete[] buffer;
		SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Window::instance()->fww_getWindowRenderer(), newSurface);
		SDL_FreeSurface(newSurface);
		return newTexture;
	}

	void TextureManager::fwtm_renderTexture(unsigned int textureID, int x, int y)
	{
		SDL_Rect destRect;
		SDL_QueryTexture(textureArray->at(textureID), NULL, NULL, &destRect.w, &destRect.h);
		destRect.x = x;
		destRect.y = Window::instance()->fww_getHeight() - y - destRect.h;
		SDL_RenderCopy(Window::instance()->fww_getWindowRenderer(), textureArray->at(textureID), NULL, &destRect);
	}

	void TextureManager::fwtm_renderTexture(unsigned int textureID, int x, int y, float ratio)
	{
		SDL_Rect destRect;
		SDL_QueryTexture(textureArray->at(textureID), NULL, NULL, &destRect.w, &destRect.h);
		destRect.w = (int)(destRect.w * ratio);
		destRect.h = (int)(destRect.h * ratio);
		destRect.x = x;
		destRect.y = Window::instance()->fww_getHeight() - y - destRect.h;
		SDL_RenderCopy(Window::instance()->fww_getWindowRenderer(), textureArray->at(textureID), NULL, &destRect);
	}

	void TextureManager::fwtm_renderTexture(unsigned int textureID, fw_Rectangle source, fw_Rectangle dest)
	{

		int tmp;
		SDL_QueryTexture(textureArray->at(textureID), NULL, NULL, NULL, &tmp);
		int wHeight = Window::instance()->fww_getHeight();

		source.y = tmp - source.y - source.h;

		dest.y = wHeight - dest.h - dest.y;

		SDL_RenderCopy(Window::instance()->fww_getWindowRenderer(), textureArray->at(textureID), &source, &dest);
	}

	void TextureManager::fwtm_renderTexture(fw_Texture* texture, int x, int y)
	{
		SDL_Rect destRect;
		SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
		destRect.x = x;
		destRect.y = Window::instance()->fww_getHeight() - y - destRect.h;
		SDL_RenderCopy(Window::instance()->fww_getWindowRenderer(), texture, NULL, &destRect);
	}


	void TextureManager::fwtm_renderTexture(fw_Texture* texture, fw_Rectangle source, fw_Rectangle dest)
	{

		int tmp;
		SDL_QueryTexture(texture, NULL, NULL, NULL, &tmp);
		int wHeight = Window::instance()->fww_getHeight();

		source.y = tmp - source.y - source.h;

		dest.y = wHeight - dest.h - dest.y;

		SDL_RenderCopy(Window::instance()->fww_getWindowRenderer(), texture, &source, &dest);
	}

	void TextureManager::fwtm_destroy()
	{
		/*	Free the texture array	*/
		for (std::vector<fw_Texture*>::iterator i = textureArray->begin(); i != textureArray->end(); i++)
		{
			SDL_DestroyTexture(*i);
		}

		textureArray->clear();

		delete textureArray;
		delete singleton;

		singleton = NULL;

		textureArray = NULL;
	}

}