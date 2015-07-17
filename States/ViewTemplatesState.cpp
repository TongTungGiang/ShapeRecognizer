//------------------------------------------------------------------------------------------
//
//  ViewTemplateState.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include "ViewTemplatesState.h"
#include <dirent.h>

ViewTemplatesState::ViewTemplatesState()
{
	stateID = VIEW_TEMPLATE_STATE;

	templateNames.clear();
	loadTemplateNames();
	if (templateNames.size() % TEMPLATES_PER_PAGE == 0)
		maxPages = templateNames.size() / TEMPLATES_PER_PAGE;
	else
		maxPages = templateNames.size() / TEMPLATES_PER_PAGE + 1;

	currentPage = 1;

	getCommandButtonManager()->createButton(fw_getFunctionAddress(ViewTemplatesState::buttonExitClicked),
		DollarRecognizer::Vector2i(400, 280),
		DollarRecognizer::Vector2i(200, 60),
		EXIT_BUTTON,
		EXIT_BUTTON_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(ViewTemplatesState::buttonBackClicked),
		DollarRecognizer::Vector2i(400, 380),
		DollarRecognizer::Vector2i(200, 60),
		BACK_BUTTON,
		BACK_BUTTON_ACTIVE);	
	getCommandButtonManager()->createButton(fw_getFunctionAddress(ViewTemplatesState::buttonNextClicked),
		DollarRecognizer::Vector2i(500, 40),
		DollarRecognizer::Vector2i(100, 60),
		NEXT_BUTTON,
		NEXT_BUTTON_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(ViewTemplatesState::buttonPrevClicked),
		DollarRecognizer::Vector2i(400, 40),
		DollarRecognizer::Vector2i(100, 60),
		PREV_BUTTON,
		PREV_BUTTON_ACTIVE);
}

ViewTemplatesState::~ViewTemplatesState()
{
	// empty body
}

void ViewTemplatesState::loadTemplateNames()
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(TEMPLATE_PATH)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
			{
				std::string fileName =ent->d_name;
				
				fileName.resize(fileName.length() - 4);
				std::string mirX = "_mirX";
				std::string mirY = "_mirY";
				std::size_t foundMirX = fileName.find(mirX);
				std::size_t foundMirY = fileName.find(mirY);
				if (foundMirX != std::string::npos || foundMirY != std::string::npos)
					continue;

				fileName = "- " + fileName;
				templateNames.push_back(fileName);
			}
		}
		closedir(dir);
	}
	else
	{
		printf("Could not open the directory %s\n", TEMPLATE_PATH);
		exit(EXIT_FAILURE);
	}
}

bool ViewTemplatesState::onEnter()
{
	Framework::InputHandler::instance()->fwi_resetCallback();

	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_LEFT_MOUSE_BUTTON_DOWN,
		fw_getFunctionAddress(ViewTemplatesState::processLeftMouseButtonDownEvent));
	Framework::InputHandler::instance()->fwi_setCallbackFunction(Framework::FW_EVENT_MOUSE_MOVE,
		fw_getFunctionAddress(ViewTemplatesState::processMouseMoveEvent));

	return true;
}

bool ViewTemplatesState::onExit()
{
	return true;
}

void ViewTemplatesState::update()
{
}

void ViewTemplatesState::render()
{
	getCommandButtonManager()->renderButtons();

	std::string pages = std::to_string(currentPage) + " / " + std::to_string(maxPages);
	Framework::FontLibrary::instance()->fwf_renderText(pages.c_str(),
		"Arial20", { 0, 0, 0, 255 }, 475, 100);

	int start = (currentPage - 1) * TEMPLATES_PER_PAGE;
	int end = currentPage * TEMPLATES_PER_PAGE - 1;
	if (end > templateNames.size() - 1)
		end = templateNames.size() - 1;
	int renderPosY = 420;
	for (int i = start; i <= end; i++)
	{
		Framework::FontLibrary::instance()->fwf_renderText(templateNames[i].c_str(),
			"Arial20", { 0, 0, 0, 255 }, 40, renderPosY);
		renderPosY -= 30;
	}
}

void ViewTemplatesState::processMouseMoveEvent()
{
	getCommandButtonManager()->browseArray_Point();
}

void ViewTemplatesState::processLeftMouseButtonDownEvent()
{
	getCommandButtonManager()->browseArray_LeftClick();
}

void ViewTemplatesState::buttonBackClicked()
{
	isOnState = false;
	setNextState(MENU_STATE);
}

void ViewTemplatesState::buttonExitClicked()
{
	isOnState = false;
	setNextState(QUIT_STATE);
}

void ViewTemplatesState::buttonNextClicked()
{
	getCommandButtonManager()->setNonActiveButton(2);
	if (currentPage >= maxPages)
		return;

	currentPage++;
}

void ViewTemplatesState::buttonPrevClicked()
{
	getCommandButtonManager()->setNonActiveButton(3);
	if (currentPage <= 1)
		return;
	
	currentPage--;
}