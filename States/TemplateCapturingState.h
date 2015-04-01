//------------------------------------------------------------------------------------------
//
//  TemplateCapturingState.h
//
//  Created by Tong Tung Giang in 2015
//
#ifndef TEMPLATECAPTURINGSTATE_H
#define TEMPLATECAPTURINGSTATE_H

#include "..\Framework\GameState.h"
#include "..\DollarRecognizer\GeometricRecognizerTypes.h"

class TemplateCapturingState : public Framework::GameState
{

private:

	bool mouseIsPressed;
	bool finishedCapturing;
	bool canCapture;
	DollarRecognizer::Path2D points;
	std::string templateName;

public:

	TemplateCapturingState();
	virtual ~TemplateCapturingState();
	
	void processLeftMouseButtonDownEvent();
	void processLeftMouseButtonUpEvent();
	void processMouseMoveEvent();

	virtual bool onEnter();
	virtual bool onExit();

	virtual void update();
	virtual void render();

	void buttonBackClicked();
	void buttonExitClicked();
	void buttonSaveClicked();
	void textboxClicked();
};

#endif