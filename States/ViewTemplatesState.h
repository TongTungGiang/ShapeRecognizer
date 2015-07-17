#ifndef VIEWTEMPLATESTATE_H
#define VIEWTEMPLATESTATE_H

//------------------------------------------------------------------------------------------
//
//  ViewTemplateState.h
//
//  Created by Tong Tung Giang in 2015
//
#include "..\Framework\GameState.h"
#include "..\DollarRecognizer\GeometricRecognizer.h"
#include <vector>
#include <string>

#define TEMPLATES_PER_PAGE 14

class ViewTemplatesState : public Framework::GameState
{

private:

	std::vector<std::string> templateNames;
	int maxPages;
	int currentPage;

public:

	ViewTemplatesState();
	~ViewTemplatesState();

	void loadTemplateNames();

	bool onEnter();
	bool onExit();

	virtual void update();
	virtual void render();

	void processMouseMoveEvent();
	void processLeftMouseButtonDownEvent();

	void buttonBackClicked();
	void buttonExitClicked();
	void buttonNextClicked();
	void buttonPrevClicked();

};

#endif