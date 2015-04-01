//------------------------------------------------------------------------------------------
//
//  GameState.h
//
//  Created by CNTA.C++ Team in 2014
//
#include "CommandButtonManager.h"
#include <functional>

#ifndef GAMESTATE_H
#define GAMESTATE_H

enum game_states
{
	RECOGNIZING_STATE,
	TEMPLATE_CAPTURING_STATE,
	MENU_STATE,
	ABOUT_STATE,
	VIEW_TEMPLATE_STATE,
	QUIT_STATE
};

namespace Framework
{
	class GameState
	{
	private:
		CommandButtonManager* buttonManager;
		int nextState;

	protected:
		bool isOnState;
		int stateID;

	public:

		GameState()
		{
			//nextState = MENU_STATE;
			buttonManager = new CommandButtonManager();
		}

		virtual ~GameState()
		{
			delete buttonManager;
		}

		virtual void update() = 0;
		virtual void render() = 0;

		void mainLoop()
		{
			int lastTime, lag, newTime, elapsed;

			lastTime = Timer::instance()->fwt_getTime();
			lag = 0;

			isOnState = true;

			while (isOnState)
			{
				onEnter();
				newTime = Timer::instance()->fwt_getTime();
				elapsed = newTime - lastTime;
				lastTime = newTime;
				lag += elapsed;

				InputHandler::instance()->fwi_PollEvent();

				while (lag >= MS_PER_UPDATE)
				{
					/*  Update game state here  */
					update();
					lag -= MS_PER_UPDATE;
				}

				/*  Render Here */
				Window::instance()->fww_clearScreen();
				render();
				Window::instance()->fww_drawScreen();
			}
		}

		virtual bool onEnter() = 0;

		virtual bool onExit() = 0;

		void setNextState(int _nextState)
		{
			nextState = _nextState;
		}

		int getNextState()
		{
			return nextState;
		}

		int getStateID()
		{
			return stateID;
		}

		CommandButtonManager* getCommandButtonManager()
		{
			return buttonManager;
		}

	};
}

#endif