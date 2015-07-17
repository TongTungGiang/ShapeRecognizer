//------------------------------------------------------------------------------------------
//
//  TextureManager.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#define fw_Rectangle SDL_Rect
#define fw_Image SDL_Surface
#define fw_Texture SDL_Texture

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <string>

#include "Window.h"

enum button_textures
{
	DRAW_PANEL,
	RESULT_PANEL,
	POINT_RED,
	BACK_BUTTON,
	BACK_BUTTON_ACTIVE,
	EXIT_BUTTON,
	EXIT_BUTTON_ACTIVE,
	SAVE_BUTTON,
	SAVE_BUTTON_ACTIVE,
	NAME_INPUT,
	TEXTBOX,
	TEXTBOX_ACTIVE,

	MENU1, MENU1_ACTIVE,  // Recognize
	MENU2, MENU2_ACTIVE,  // Add a template
	MENU3, MENU3_ACTIVE,  // View templates
	MENU4, MENU4_ACTIVE,  // About
	MENU5, MENU5_ACTIVE,   // Exit

	NEXT_BUTTON, NEXT_BUTTON_ACTIVE,
	PREV_BUTTON, PREV_BUTTON_ACTIVE,

	CREDIT
};

namespace Framework
{

	class TextureManager
	{
	private:
		static TextureManager* singleton;
		TextureManager() {};
		static unsigned int iterator_texture;
		static std::vector <fw_Texture*> *textureArray;

	public:
		static TextureManager* instance()
		{
			if (singleton == NULL)
			{
				singleton = new TextureManager;
			}
			return singleton;
		}

		void fwtm_initialize();
		unsigned int fwtm_createTextureFromFile(std::string filename);
		fw_Texture* fwtm_createTempTextureFromFile(std::wstring filename);

		void fwtm_renderTexture(unsigned int textureID, int x, int y);
		void fwtm_renderTexture(unsigned int textureID, int x, int y, float ratio);
		void fwtm_renderTexture(unsigned int textureID, fw_Rectangle source, fw_Rectangle dest);

		void fwtm_renderTexture(fw_Texture* texture, int x, int y);
		void fwtm_renderTexture(fw_Texture* texture, fw_Rectangle source, fw_Rectangle dest);
		void fwtm_destroy();

		~TextureManager() {};
	};

}

#endif