//------------------------------------------------------------------------------------------
//
//  Window.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_syswm.h>
#include <Windows.h>

namespace Framework
{

	class Window
	{
	private:

		static Window* singleton;

		static SDL_Window* p_window;
		static SDL_Renderer* p_renderer;

		static bool isCreated;

		static int windowWidth;
		static int windowHeight;

		Window() {};

	public:
		static Window* instance()
		{
			if (singleton == NULL)
			{
				singleton = new Window;
			}
			return singleton;
		}

		void fww_initialize();

		void fww_createWindow(const char* title, int xPosition, int yPosition, int width, int height);

		int fww_getWidth();
		int fww_getHeight();

		void fww_setClearColor(int red, int green, int blue, int alpha);

		void fww_clearScreen();
		void fww_drawScreen();

		void fww_captureScreen(char* savepath);

		HWND fww_getWindowHandle();

		unsigned int fww_displayMessageBox(wchar_t *title, wchar_t *content, unsigned int msgBoxType);

		SDL_Renderer* fww_getWindowRenderer();

		void fww_destroy();
	};
}

#endif