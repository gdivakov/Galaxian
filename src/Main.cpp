#include <SDL.h>
#include <iostream>

#include "App.h"
#include "Level1.h"
#include "MainScreen.h"
#include "Consts.h"

int main(int argc, char* args[])
{
	App galaxian(WINDOWED_WIDTH, WINDOWED_HEIGHT);
	
	if (!galaxian.getStatus())
	{
		std::cout << galaxian.getErrMessage() << std::endl;

		return 0;
	}

	Loop* gameLoop = galaxian.getGameLoop();

	MainScreen main(&galaxian);
	Level1 level1(&galaxian);

	main.start();
	level1.start();

	return 0;
}