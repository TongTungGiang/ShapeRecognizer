//------------------------------------------------------------------------------------------
//
//  MenuState.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include "MenuState.h"

MenuState::MenuState()
{
	stateID = MENU_STATE;

	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::goToRecognize),
		DollarRecognizer::Vector2i(220, 300),
		DollarRecognizer::Vector2i(200, 60),
		MENU1,
		MENU1_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::goToTemplateCapturing),
		DollarRecognizer::Vector2i(220, 240),
		DollarRecognizer::Vector2i(200, 60),
		MENU2,
		MENU2_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::goToViewTemplates),
		DollarRecognizer::Vector2i(220, 180),
		DollarRecognizer::Vector2i(200, 60),
		MENU3,
		MENU3_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::goToAbout),
		DollarRecognizer::Vector2i(220, 120),
		DollarRecognizer::Vector2i(200, 60),
		MENU4,
		MENU4_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::goToExit),
		DollarRecognizer::Vector2i(220, 60),
		DollarRecognizer::Vector2i(200, 60),
		MENU5,
		MENU5_ACTIVE);
}

MenuState::~MenuState()
{
	// empty body
}

bool MenuState::onEnter()
{
	Framework::InputHandler::instance()->fwi_resetCallback();

	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_LEFT_MOUSE_BUTTON_DOWN,
		fw_getFunctionAddress(MenuState::processLeftMouseButtonDownEvent));
	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_MOUSE_MOVE,
		fw_getFunctionAddress(MenuState::processMouseMoveEvent));

	return true;
}

bool MenuState::onExit()
{
	return true;
}


void MenuState::update()
{
	// empty body
}

void MenuState::render()
{
	getCommandButtonManager()->renderButtons();
}

void MenuState::processMouseMoveEvent()
{
	getCommandButtonManager()->browseArray_Point();
}

void MenuState::processLeftMouseButtonDownEvent()
{
	getCommandButtonManager()->browseArray_LeftClick();
}

void MenuState::goToRecognize()
{
	isOnState = false;
	setNextState(RECOGNIZING_STATE);
}

void MenuState::goToTemplateCapturing()
{
	isOnState = false;
	setNextState(TEMPLATE_CAPTURING_STATE);
}

void MenuState::goToViewTemplates()
{
	isOnState = false;
	setNextState(QUIT_STATE);
}

void MenuState::goToAbout()
{
	isOnState = false;
	setNextState(QUIT_STATE);
}

void MenuState::goToExit()
{
	isOnState = false;
	setNextState(QUIT_STATE);
}