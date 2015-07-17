#ifndef CREDITSTATE_H
#define CREDITSTATE_H

#include "..\Framework\GameState.h"

class CreditState : public Framework::GameState
{

public:

	CreditState();
	~CreditState();
	
	bool onEnter();
	bool onExit();

	virtual void update();
	virtual void render();

	void processMouseMoveEvent();
	void processLeftMouseButtonDownEvent();

	void buttonBackClicked();
	void buttonExitClicked();

};

#endif