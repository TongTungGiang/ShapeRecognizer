//------------------------------------------------------------------------------------------
//
//  GameStateManager.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "..\States\RecognizingState.h"
#include "..\States\TemplateCapturingState.h"
#include "..\States\MenuState.h"
#include "..\States\ViewTemplatesState.h"
#include "..\States\CreditState.h"

#include <vector>

namespace Framework
{

	class GameStateManager
	{

	private:
		std::vector < GameState* >* gameStates;

	public:

		GameStateManager()
		{
			gameStates = new std::vector < GameState* > ;
			pushState(new MenuState);
		}

		~GameStateManager()
		{
			delete gameStates;
		}

		void pushState(GameState* pState)
		{
			gameStates->push_back(pState);
			gameStates->back()->onEnter();
		}

		void changeState(GameState *pState)
		{
			if (!gameStates->empty())
			{
				popState();
			}

			pushState(pState);
		}

		void popState()
		{
			if (!gameStates->empty())
			{
				if (gameStates->back()->onExit())
				{
					delete gameStates->back();
					gameStates->pop_back();
				}
			}
		}

		void run()
		{
			while (gameStates->size() > 0)
			{
				getCurrentState()->mainLoop();
				//InputHandler::instance()->fwi_resetCallback();
				switch (getCurrentState()->getNextState())
				{
				case RECOGNIZING_STATE:
					changeState(new RecognizingState()); break;
				case TEMPLATE_CAPTURING_STATE:
					changeState(new TemplateCapturingState()); break;
				case MENU_STATE:
					changeState(new MenuState()); break;
				case VIEW_TEMPLATE_STATE:
					changeState(new ViewTemplatesState()); break;
				case CREDIT_STATE:
					changeState(new CreditState()); break;
				case QUIT_STATE:
					popState(); break;
				default:
					break;
				}
			}
		}

		GameState* getCurrentState()
		{
			return gameStates->back();
		}

	};

}

#endif
