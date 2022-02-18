#include <SDL.h>
#include <iostream>

#include "App.h"
#include "Level.h"
#include "Consts.h"

int main(int argc, char* args[])
{
	App galaxian(920, 620); // Todo: to update
	
	if (!galaxian.getStatus())
	{
		std::cout << galaxian.getErrMessage() << std::endl;

		return 0;
	}

	galaxian.toggleWindowed();

	Level level1(&galaxian);
	level1.start();

	return 0;
}