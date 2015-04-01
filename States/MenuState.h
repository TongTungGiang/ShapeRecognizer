//------------------------------------------------------------------------------------------
//
//  MenuState.h
//
//  Created by Tong Tung Giang in 2015
//
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "..\Framework\GameState.h"

class MenuState : public Framework::GameState
{

public:

	MenuState();
	~MenuState();

	bool onEnter();
	bool onExit();

	virtual void update();
	virtual void render();

	void processMouseMoveEvent();
	void processLeftMouseButtonDownEvent();

	void goToRecognize();
	void goToTemplateCapturing();
	void goToViewTemplates();
	void goToAbout();
	void goToExit();

};

#endif