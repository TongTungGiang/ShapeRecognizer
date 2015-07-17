//------------------------------------------------------------------------------------------
//
//  TemplateCapturingState.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include "TemplateCapturingState.h"
#include <fstream>
#include "..\DollarRecognizer\GeometricRecognizer.h"
#include <iomanip>

TemplateCapturingState::TemplateCapturingState()
{
	stateID = TEMPLATE_CAPTURING_STATE;
	mouseIsPressed = false;
	finishedCapturing = false;
	canCapture = true;

	isOnState = true;
	points.clear();
	templateName = "";

	getCommandButtonManager()->createButton(fw_getFunctionAddress(TemplateCapturingState::buttonExitClicked),
		DollarRecognizer::Vector2i(400, 280),
		DollarRecognizer::Vector2i(200, 60),
		EXIT_BUTTON,
		EXIT_BUTTON_ACTIVE); 
	getCommandButtonManager()->createButton(fw_getFunctionAddress(TemplateCapturingState::buttonBackClicked),
		DollarRecognizer::Vector2i(400, 380),
		DollarRecognizer::Vector2i(200, 60),
		BACK_BUTTON,
		BACK_BUTTON_ACTIVE); 
	getCommandButtonManager()->createButton(fw_getFunctionAddress(TemplateCapturingState::buttonSaveClicked),
		DollarRecognizer::Vector2i(400, 40),
		DollarRecognizer::Vector2i(200, 60),
		SAVE_BUTTON,
		SAVE_BUTTON_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(TemplateCapturingState::textboxClicked),
		DollarRecognizer::Vector2i(400, 120),
		DollarRecognizer::Vector2i(200, 61),
		TEXTBOX,
		TEXTBOX_ACTIVE);
}

TemplateCapturingState::~TemplateCapturingState()
{
	// empty body
}

bool TemplateCapturingState::onEnter()
{
	Framework::InputHandler::instance()->fwi_resetCallback();

	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_LEFT_MOUSE_BUTTON_DOWN,
		fw_getFunctionAddress(TemplateCapturingState::processLeftMouseButtonDownEvent));
	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_LEFT_MOUSE_BUTTON_UP,
		fw_getFunctionAddress(TemplateCapturingState::processLeftMouseButtonUpEvent));
	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_MOUSE_MOVE,
		fw_getFunctionAddress(TemplateCapturingState::processMouseMoveEvent));

	return true;
}

bool TemplateCapturingState::onExit()
{
	return true;
}

void TemplateCapturingState::buttonBackClicked()
{
	isOnState = false;
	setNextState(MENU_STATE);
}

void TemplateCapturingState::buttonExitClicked()
{
	isOnState = false;
	setNextState(QUIT_STATE);
}

void TemplateCapturingState::buttonSaveClicked()
{
	getCommandButtonManager()->setNonActiveButton(2);

	if (templateName == "")
		return;

	normalizeString(&templateName);

	// Save the template
	std::string path = "resources/templates/" + templateName + ".txt";
	std::ofstream ofs(path);
	ofs << templateName << std::endl;
	DollarRecognizer::GeometricRecognizer rec(TEMPLATE_PATH);
	DollarRecognizer::Path2D temp = rec.normalizePath(points);
	for (int i = 0; i < temp.size(); i++)
	{
		ofs << std::fixed << std::setprecision(2) << temp[i].x << " " << temp[i].y << std::endl;
	}

	// Save the template - mirrored via X axis
	path = "resources/templates/" + templateName + "_mirX.txt";
	ofs = ofstream(path);
	ofs << templateName << std::endl;
	for (int i = 0; i < temp.size(); i++)
	{
		ofs << std::fixed << std::setprecision(2) << temp[i].x << " " << -temp[i].y << std::endl;
	}

	// Save the template - mirrored via Y axis
	path = "resources/templates/" + templateName + "_mirY.txt";
	ofs = ofstream(path);
	ofs << templateName << std::endl;
	for (int i = 0; i < temp.size(); i++)
	{
		ofs << std::fixed << std::setprecision(2) << -temp[i].x << " " << temp[i].y << std::endl;
	}
}

void TemplateCapturingState::textboxClicked()
{
	Framework::InputHandler::instance()->fwi_startStringCapture("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_ ");
	Framework::InputHandler::instance()->fwi_setCapturedString(&templateName, 16);
}

void TemplateCapturingState::processMouseMoveEvent()
{
	int mouseX, mouseY;

	Framework::InputHandler::instance()->fwi_getMousePosition(&mouseX, &mouseY);
	mouseY = Framework::Window::instance()->fww_getHeight() - mouseY;

	if (mouseX > 40 && mouseX < 340 &&
		mouseY > 40 && mouseY < 340 && canCapture) // if mouse is inside draw panel
	{
		if (mouseIsPressed)
			points.push_back(DollarRecognizer::Point2D(mouseX, mouseY)); // add new point to candidate path
	}
	else
		getCommandButtonManager()->browseArray_Point();
}

void TemplateCapturingState::processLeftMouseButtonDownEvent()
{
	int mouseX, mouseY;

	Framework::InputHandler::instance()->fwi_getMousePosition(&mouseX, &mouseY);
	mouseY = Framework::Window::instance()->fww_getHeight() - mouseY;

	mouseIsPressed = true;
	if (mouseX > 40 && mouseX < 340 &&
		mouseY > 40 && mouseY < 340) // if mouse is inside draw panel
	{
		if (canCapture)
			points.push_back(DollarRecognizer::Point2D(mouseX, mouseY)); // add new point to candidate path
		else
		{
			if (points.size() == 0) // not capture yet
				canCapture = true;
		}
	}
	else
	{
		getCommandButtonManager()->browseArray_LeftClick();
		finishedCapturing = true;
	}
}

void TemplateCapturingState::processLeftMouseButtonUpEvent()
{
	mouseIsPressed = false;
	canCapture = false;
	finishedCapturing = true;
}

void TemplateCapturingState::update()
{
}

void TemplateCapturingState::render()
{
	Framework::TextureManager::instance()->fwtm_renderTexture(DRAW_PANEL, 40, 40);
	Framework::TextureManager::instance()->fwtm_renderTexture(NAME_INPUT, 400, 120);

	for (int i = 0; i < points.size(); i++)
	{
		DollarRecognizer::Point2D currentPoint = points[i];
		Framework::TextureManager::instance()->fwtm_renderTexture(POINT_RED, currentPoint.x - 2, currentPoint.y - 2);
	}

	getCommandButtonManager()->renderButtons();

	int x = getCommandButtonManager()->getButtonOriginCoordinates(3).x;
	int y = getCommandButtonManager()->getButtonOriginCoordinates(3).y;

	Framework::FontLibrary::instance()->fwf_renderText(templateName.c_str(),
		"Arial20", { 0, 0, 0, 255 }, x + 10, y + 15);
}

void TemplateCapturingState::normalizeString(std::string *s)
{
	while (s->at(0) == ' ')
		s->erase(0, 1);

	while (s->at(s->length() - 1) == ' ')
		s->erase(s->length() - 1, 1);

	s->at(0) = toupper(s->at(0));
	for (int i = 1; i < s->length() - 1; i++)
	{
		if (s->at(i) == ' ')
		{
			while (s->at(i + 1) == ' ')
				s->erase(i, 1);
			s->at(i + 1) = toupper(s->at(i + 1));
		}
	}
}