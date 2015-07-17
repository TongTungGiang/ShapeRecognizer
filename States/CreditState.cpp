#include "CreditState.h"

CreditState::CreditState()
{
	stateID = CREDIT_STATE;

	getCommandButtonManager()->createButton(fw_getFunctionAddress(CreditState::buttonExitClicked),
		DollarRecognizer::Vector2i(440, 280),
		DollarRecognizer::Vector2i(200, 60),
		EXIT_BUTTON,
		EXIT_BUTTON_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(CreditState::buttonBackClicked),
		DollarRecognizer::Vector2i(440, 380),
		DollarRecognizer::Vector2i(200, 60),
		BACK_BUTTON,
		BACK_BUTTON_ACTIVE);
}

CreditState::~CreditState()
{
	// empty body
}

bool CreditState::onEnter()
{
	Framework::InputHandler::instance()->fwi_resetCallback();

	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_LEFT_MOUSE_BUTTON_DOWN,
		fw_getFunctionAddress(CreditState::processLeftMouseButtonDownEvent));
	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_MOUSE_MOVE,
		fw_getFunctionAddress(CreditState::processMouseMoveEvent));

	return true;
}

bool CreditState::onExit()
{
	return true;
}

void CreditState::update()
{
	// empty body
}

void CreditState::render()
{
	Framework::TextureManager::instance()->fwtm_renderTexture(CREDIT, 0, 0);
	getCommandButtonManager()->renderButtons();
}

void CreditState::processMouseMoveEvent()
{
	getCommandButtonManager()->browseArray_Point();
}

void CreditState::processLeftMouseButtonDownEvent()
{
	getCommandButtonManager()->browseArray_LeftClick();
}

void CreditState::buttonBackClicked()
{
	isOnState = false;
	setNextState(MENU_STATE);
}

void CreditState::buttonExitClicked()
{
	isOnState = false;
	setNextState(QUIT_STATE);
}