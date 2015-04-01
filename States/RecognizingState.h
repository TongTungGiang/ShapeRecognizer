//------------------------------------------------------------------------------------------
//
//  RecognizingState.h
//
//  Created by Tong Tung Giang in 2015
//
#ifndef RECOGNIZINGSTATE_H
#define RECOGNIZINGSTATE_H

#include "../DollarRecognizer/GeometricRecognizer.h"
#include "../Framework/GameState.h"
#include "../Framework/FrameWork.h"

class RecognizingState : public Framework::GameState
{

private:

	DollarRecognizer::GeometricRecognizer* recognizer;
	DollarRecognizer::Path2D candidate;
	std::string result;
	bool mouseIsPressed;
	bool finishedCapturing;
	bool canCapture;
	
public:

	RecognizingState();
	virtual ~RecognizingState();

	void processLeftMouseButtonDownEvent();
	void processLeftMouseButtonUpEvent();
	void processMouseMoveEvent();

	virtual bool onEnter();
	virtual bool onExit();
	
	virtual void update();
	virtual void render();

	void buttonBackClicked();
	void buttonExitClicked();

};

#endif