#include <SDL.h>
#include <iostream>

#include "App.h"
#include "Level.h"
#include "Consts.h"

int main(int argc, char* args[])
{
	App galaxian(WINDOWED_WIDTH, WINDOWED_HEIGHT);
	
	if (!galaxian.getStatus())
	{
		std::cout << galaxian.getErrMessage() << std::endl;

		return 0;
	}

	Level level1(&galaxian);
	level1.start();

	return 0;
}