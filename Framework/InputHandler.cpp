//------------------------------------------------------------------------------------------
//
//  InputHandler.cpp
//
//  Created by CNTA.C++ Team in 2014
//
#include "InputHandler.h"

namespace Framework
{
	
	InputHandler* InputHandler::singleton = NULL;

	int InputHandler::xMouse = 0;
	int InputHandler::yMouse = 0;

	bool InputHandler::isStringCapturing = false;
	std::string InputHandler::receptedCharacters = "";
	std::string* InputHandler::stringPointer = NULL;
	unsigned int InputHandler::maxStringLength = 0;

	std::function<void()> InputHandler::quit_callback = nullptr;
	std::function<void()> InputHandler::leftMouseButtonsUp_callback = nullptr;
	std::function<void()> InputHandler::leftMouseButtonsDown_callback = nullptr;
	std::function<void()> InputHandler::rightMouseButtonsUp_callback = nullptr;
	std::function<void()> InputHandler::rightMouseButtonsDown_callback = nullptr;
	std::function<void()> InputHandler::middleMouseButtonsUp_callback = nullptr;
	std::function<void()> InputHandler::middleMouseButtonsDown_callback = nullptr;
	std::function<void()> InputHandler::mouseMove_callback = nullptr;

	void InputHandler::fwi_initialize()
	{

	}

	void InputHandler::fwi_PollEvent()
	{
		SDL_Event ev;

		while (SDL_PollEvent(&ev))
		{
			xMouse = ev.button.x;
			yMouse = ev.button.y;
			if (ev.type == SDL_QUIT)
			{
				if (quit_callback != nullptr)
				{
					quit_callback();
				}
			}

			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (ev.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (leftMouseButtonsDown_callback != nullptr)
					{
						leftMouseButtonsDown_callback();
					}
					break;
				case SDL_BUTTON_RIGHT:
					if (rightMouseButtonsDown_callback != nullptr)
					{
						rightMouseButtonsDown_callback();
					}
					break;
				case SDL_BUTTON_MIDDLE:
					if (middleMouseButtonsDown_callback != nullptr)
					{
						middleMouseButtonsDown_callback();
					}
					break;
				}
			}

			if (ev.type == SDL_MOUSEBUTTONUP)
			{
				switch (ev.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (leftMouseButtonsUp_callback != nullptr)
					{
						leftMouseButtonsUp_callback();
					}
					break;
				case SDL_BUTTON_RIGHT:
					if (rightMouseButtonsUp_callback != nullptr)
					{
						rightMouseButtonsUp_callback();
					}
					break;
				case SDL_BUTTON_MIDDLE:
					if (middleMouseButtonsUp_callback != nullptr)
					{
						middleMouseButtonsUp_callback();
					}
					break;
				}
			}

			if (ev.type == SDL_MOUSEMOTION)
			{
				if (mouseMove_callback != nullptr)
				{
					mouseMove_callback();
				}
			}

			if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
			{
				if (isStringCapturing)
				{
					if (ev.type == SDL_KEYDOWN)
					{
						if (ev.key.keysym.sym == SDLK_BACKSPACE && (*stringPointer).length() > 0)
						{
							*stringPointer = (*stringPointer).substr(0, (*stringPointer).length() - 1);
						}
					}
					else if (ev.type == SDL_TEXTINPUT)
					{
						std::string tmp = ev.text.text;
						if (tmp.find_first_not_of(receptedCharacters) == std::string::npos)
						{
							if ((*stringPointer).length() + tmp.length() <= maxStringLength)
							{
								*stringPointer += tmp;
							}
						}
					}
				}
			}
		}
	}

	void InputHandler::fwi_startStringCapture(std::string receptedCharacters)
	{
		isStringCapturing = true;
		this->receptedCharacters = receptedCharacters;
	}

	void InputHandler::fwi_setCapturedString(std::string* str, int maxStringLength)
	{
		stringPointer = str;
		this->maxStringLength = maxStringLength;
	}

	void InputHandler::fwi_stopStringCapture()
	{
		isStringCapturing = false;
		receptedCharacters = "";
		stringPointer = NULL;
	}

	void InputHandler::fwi_getMousePosition(int* x, int* y)
	{
		if (x) *x = xMouse;
		if (y) *y = yMouse;
	}

	//void InputHandler::fwi_setCallbackFunction(unsigned int event_type, std::function<void()> const &function_pointer)
	void InputHandler::fwi_setCallbackFunction(unsigned int event_type, std::function<void()> function_pointer)
	{
		switch (event_type)
		{
		case FW_EVENT_QUIT:
			quit_callback = function_pointer;
			break;

		case FW_EVENT_LEFT_MOUSE_BUTTON_UP:
			leftMouseButtonsUp_callback = function_pointer;
			break;

		case FW_EVENT_LEFT_MOUSE_BUTTON_DOWN:
			leftMouseButtonsDown_callback = function_pointer;
			break;

		case FW_EVENT_RIGHT_MOUSE_BUTTON_UP:
			rightMouseButtonsUp_callback = function_pointer;
			break;

		case FW_EVENT_RIGHT_MOUSE_BUTTON_DOWN:
			rightMouseButtonsDown_callback = function_pointer;
			break;

		case FW_EVENT_MIDDLE_MOUSE_BUTTON_UP:
			middleMouseButtonsUp_callback = function_pointer;
			break;

		case FW_EVENT_MIDDLE_MOUSE_BUTTON_DOWN:
			middleMouseButtonsDown_callback = function_pointer;
			break;

		case FW_EVENT_MOUSE_MOVE:
			mouseMove_callback = function_pointer;
			break;

		}
	}

	void InputHandler::fwi_resetCallback()
	{
		quit_callback = nullptr;
		leftMouseButtonsUp_callback = nullptr;
		leftMouseButtonsDown_callback = nullptr;
		rightMouseButtonsUp_callback = nullptr;
		rightMouseButtonsDown_callback = nullptr;
		middleMouseButtonsUp_callback = nullptr;
		middleMouseButtonsDown_callback = nullptr;
		mouseMove_callback = nullptr;
	}

	void InputHandler::fwi_destroy()
	{
		delete singleton;
	}

}