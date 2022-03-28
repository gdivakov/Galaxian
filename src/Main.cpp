#include <SDL.h>
#include <iostream>

#include "App.h"
#include "Consts.h"
#include "LevelManager.h"

int main(int argc, char* args[])
{
	App galaxian(WINDOWED_WIDTH, WINDOWED_HEIGHT);
	
	if (!galaxian.getStatus())
	{
		std::cout << galaxian.getErrMessage() << std::endl;

		return 0;
	}

	LevelManager levels(&galaxian);

	levels.start(MAIN_MENU);

	return 0;
}