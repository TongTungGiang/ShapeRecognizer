//------------------------------------------------------------------------------------------
//
//  Framework.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "FontLibrary.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Window.h"
#include "Timer.h"

#define MS_PER_UPDATE 1

namespace Framework
{

	static void fw_setRectDimension(fw_Rectangle* rect, int x, int y, int width, int height)
	{
		rect->x = x;
		rect->y = y;
		rect->w = width;
		rect->h = height;
	}


	static bool fw_frameworkInitialize()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		{
			Window::instance()->fww_initialize();
			InputHandler::instance()->fwi_initialize();
			TextureManager::instance()->fwtm_initialize();
			FontLibrary::instance()->fwf_initialize();
			return true;
		}
		return false;
	}

	static void fw_frameworkTerminate()
	{
		FontLibrary::instance()->fwf_destroy();
		InputHandler::instance()->fwi_destroy();
		TextureManager::instance()->fwtm_destroy();
		Window::instance()->fww_destroy();
		SDL_Quit();
	}
}

#endif