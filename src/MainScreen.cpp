#include "MainScreen.h"
#include "Background.h"

MainScreen::MainScreen(const App* p_system) : Level(p_system)
{
	isActive = true;
}

void MainScreen::start()
{
	Background bgMain(renderer, "res/main_screen_bg.png", STATIC, system);
	ControlPanel panel(renderer);

	eventListeners = { &bgMain };
	renderListeners = { &bgMain };

	Loop* gameLoop = system->getGameLoop();

	// Add level objects
	gameLoop->addEventListeners(eventListeners);
	gameLoop->addRenderListeners(renderListeners);
	gameLoop->start();
	// Remove level objects
	gameLoop->removeEventListeners(eventListeners);
	gameLoop->removeRenderListeners(renderListeners);
}