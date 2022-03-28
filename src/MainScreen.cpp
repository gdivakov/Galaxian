#include "MainScreen.h"
#include "Background.h"
#include "ControlPanel.h"

void MainScreen::load()
{
	Background* bgMain = new Background(renderer, "res/main_screen_bg.png", STATIC);
	ControlPanel* panel = new ControlPanel(renderer, system, this);

	eventListeners = { panel };
	renderListeners = { bgMain, panel };
	objsToFree = { panel, bgMain };

	registerListeners();
}

void MainScreen::startGame()
{
	controller->start(LEVEL_1);
}

void MainScreen::quit()
{
	controller->stop();
}