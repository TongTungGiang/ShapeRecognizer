//------------------------------------------------------------------------------------------
//
//  RecognizingState.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include "RecognizingState.h"

RecognizingState::RecognizingState()
	: GameState()
{
	stateID = RECOGNIZING_STATE;
	recognizer = new DollarRecognizer::GeometricRecognizer(TEMPLATE_PATH);
	mouseIsPressed = false;
	finishedCapturing = false;
	isOnState = true;
	canCapture = true;
	result = "";
	candidate.clear();

	getCommandButtonManager()->createButton(fw_getFunctionAddress(RecognizingState::buttonExitClicked),
		DollarRecognizer::Vector2i(400, 280),
		DollarRecognizer::Vector2i(200, 60),
		EXIT_BUTTON,
		EXIT_BUTTON_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(RecognizingState::buttonBackClicked),
		DollarRecognizer::Vector2i(400, 380),
		DollarRecognizer::Vector2i(200, 60),
		BACK_BUTTON,
		BACK_BUTTON_ACTIVE);
}

RecognizingState::~RecognizingState()
{
	delete recognizer;
}

bool RecognizingState::onEnter()
{
	Framework::InputHandler::instance()->fwi_resetCallback();

	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_LEFT_MOUSE_BUTTON_DOWN,
		fw_getFunctionAddress(RecognizingState::processLeftMouseButtonDownEvent));
	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_LEFT_MOUSE_BUTTON_UP,
		fw_getFunctionAddress(RecognizingState::processLeftMouseButtonUpEvent));
	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_MOUSE_MOVE,
		fw_getFunctionAddress(RecognizingState::processMouseMoveEvent));

	return true;
}

bool RecognizingState::onExit()
{
	return true;
}

void RecognizingState::processMouseMoveEvent()
{
	int mouseX, mouseY;

	Framework::InputHandler::instance()->fwi_getMousePosition(&mouseX, &mouseY);
	mouseY = Framework::Window::instance()->fww_getHeight() - mouseY;

	if (mouseX > 40 && mouseX < 340 &&
		mouseY > 40 && mouseY < 340 && canCapture) // if mouse is inside draw panel
	{
		if (mouseIsPressed)
			candidate.push_back(DollarRecognizer::Point2D(mouseX, mouseY)); // add new point to candidate path
	}
	else
	{
		getCommandButtonManager()->browseArray_Point();
		canCapture = false;
	}
}

void RecognizingState::processLeftMouseButtonDownEvent()
{
	int mouseX, mouseY;

	Framework::InputHandler::instance()->fwi_getMousePosition(&mouseX, &mouseY);
	mouseY = Framework::Window::instance()->fww_getHeight() - mouseY;

	mouseIsPressed = true;

	if (mouseX > 40 && mouseX < 340 &&
		mouseY > 40 && mouseY < 340) // if mouse is inside draw panel
	{
		if (canCapture)
			candidate.push_back(DollarRecognizer::Point2D(mouseX, mouseY)); // add new point to candidate path
		else
		{
			canCapture = true;
			candidate.clear();
			candidate.push_back(DollarRecognizer::Point2D(mouseX, mouseY));
		}
	}
	else
	{
		getCommandButtonManager()->browseArray_LeftClick();
		finishedCapturing = true;
	}
}

void RecognizingState::processLeftMouseButtonUpEvent()
{
	mouseIsPressed = false;
	finishedCapturing = true;
	canCapture = false;
}

void RecognizingState::update()
{
	if (finishedCapturing && candidate.size() > 0)
	{
		DollarRecognizer::Path2D temp = candidate;
		for (int i = 0; i < temp.size(); i++)
		{
			temp[i].x = (temp[i].x - 40);

			temp[i].y = 300 - (temp[i].y - 40);
		}
		result = recognizer->recognize(temp).name;
		finishedCapturing = false;
		//candidate.clear();
	}
}

void RecognizingState::render()
{
	Framework::TextureManager::instance()->fwtm_renderTexture(DRAW_PANEL, 40, 40);
	Framework::TextureManager::instance()->fwtm_renderTexture(RESULT_PANEL, 400, 40);

	for (int i = 0; i < candidate.size(); i++)
	{
		DollarRecognizer::Point2D currentPoint = candidate[i];
		Framework::TextureManager::instance()->fwtm_renderTexture(POINT_RED, currentPoint.x - 2, currentPoint.y - 2);
	}

	Framework::FontLibrary::instance()->fwf_renderText(result.c_str(), "Arial20", { 0, 0, 0, 255 }, 420, 150);
		
	getCommandButtonManager()->renderButtons();
}

void RecognizingState::buttonBackClicked()
{
	isOnState = false;
	setNextState(MENU_STATE);
}

void RecognizingState::buttonExitClicked()
{
	isOnState = false;
	setNextState(QUIT_STATE);
}