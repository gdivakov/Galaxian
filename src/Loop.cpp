#include "Loop.h"
#include <iostream>

Loop::Loop(SDL_Renderer* p_renderer)
{
	renderer = p_renderer;
}

bool Loop::start(RenderHandler onBeforeRender, RenderHandler onAfterRender, Level* level)
{
	bool quit = false;
	SDL_Event e;

	while (!quit)
	{
		// Event loop
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			// Handle listeners
			for (int i = 0; i < listeners.size(); i++)
			{
				listeners[i]->handleEvent(e);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		onBeforeRender(level);
		SDL_RenderPresent(renderer);
		onAfterRender(level);
	}
	return true;
}

Loop::~Loop()
{}

void Loop::addEventListener(Object* listenObject)
{
	listeners.push_back(listenObject);
}

void Loop::addEventListeners(std::vector<Object*>& listenObjects)
{
	for (int i = 0; i < listenObjects.size(); i++)
	{
		addEventListener(listenObjects[i]);
	}
}

void Loop::removeListener()
{}