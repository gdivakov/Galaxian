#include "MainScreen.h"
#include "Background.h"
#include "ControlPanel.h"
#include "SoundConst.h"

void MainScreen::load()
{
	Background* bgMain = new Background(renderer, "res/main_screen_bg.png", this, false);
	ControlPanel* panel = new ControlPanel(renderer, system, this);

	eventListeners = { panel };
	renderListeners = { bgMain, panel };
	objsToFree = { panel, bgMain };

	registerListeners();

	initAudio();
}

void MainScreen::startGame()
{
	controller->start(LEVEL_1);
}

void MainScreen::initAudio()
{
	Audio* audioPlayer = system->getAudioPlayer();

	// Load level sounds
	for (int i = 0; i < LEVEL_0_SOUNDS.size(); i++)
	{
		audioPlayer->loadSound(LEVEL_0_SOUNDS[i]);
	}
}