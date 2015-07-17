//------------------------------------------------------------------------------------------
//
//  main.cpp
//
//  Created by Tong Tung Giang in 2015
//
#include <iostream>

#include "Framework\FrameWork.h"
#include "Framework\GameStateManager.h"

void loadTextures();
void loadFonts();

int main(int argc, char * argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	Framework::GameStateManager *man = new Framework::GameStateManager();

	Framework::fw_frameworkInitialize();

	Framework::Window::instance()->fww_createWindow("Shape Recognizer",
		100, 100,
		640, 480);
	Framework::Window::instance()->fww_setClearColor(238, 243, 250, 255);

	loadTextures();
	loadFonts();

	man->run();

	Framework::fw_frameworkTerminate();

	return 0;
}

void loadTextures()
{
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/DrawPanel.png"); //DRAW_PANEL,
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/ResultPanel.png"); //RESULT_PANEL
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/Point.png"); //POINT
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/BackButton.png"); //BACK_BUTTON,
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/BackButtonActive.png"); //BACK_BUTTON_ACTIVE,
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/ExitButton.png"); //EXIT_BUTTON
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/ExitButtonActive.png"); //EXIT_BUTTON_ACTIVE
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/SaveButton.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/SaveButtonActive.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/NameInput.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/Textbox.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/TextboxActive.png");

	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuRecognize.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuRecognizeActive.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuAddATemplate.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuAddATemplateActive.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuViewTemplates.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuViewTemplatesActive.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuAbout.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuAboutActive.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuExit.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/MenuExitActive.png");

	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/next.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/nextActive.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/prev.png");
	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/prevActive.png");

	Framework::TextureManager::instance()->fwtm_createTextureFromFile("resources/images/CreditBackground.png");
}

void loadFonts()
{
	Framework::FontLibrary::instance()->fwf_loadFont("resources/fonts/arial.ttf", "Arial20", 20);
}