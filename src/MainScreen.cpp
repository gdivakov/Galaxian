#include "MainScreen.h"
#include "Background.h"
#include "ControlPanel.h"
#include "SoundConst.h"

MainScreen::~MainScreen()
{
	panel = NULL;
	selectShipView = NULL;
}

void MainScreen::load()
{
	Background* bgMain = new Background(renderer, "res/sprites/backgrounds/main_screen_bg.png");
	panel = new ControlPanel(renderer, system, this);
	selectShipView = new SelectShipView(this);

	eventListeners = { selectShipView, panel };
	renderListeners = { bgMain, panel, selectShipView };
	objsToFree = { panel, bgMain, selectShipView };

	registerListeners();

	initAudio();
}

void MainScreen::handleCompleted()
{
	panel->setIsActive(false);

	if (selectShipView->getIsShipSelected())
	{
		return controller->start(LEVEL_1);
	}

	// Select ship
	selectShipView->show();
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