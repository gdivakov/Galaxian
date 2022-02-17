#include <SDL.h>
#include <iostream>

#include "App.h"
#include "Level.h"
#include "Consts.h"

int main(int argc, char* args[])
{
	App galaxian(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if (!galaxian.getStatus())
	{
		std::cout << galaxian.getErrMessage() << std::endl;

		return 0;
	}

	Level level1(galaxian.getRenderer());
	level1.start();

	return 0;
}