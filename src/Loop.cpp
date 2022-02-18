#include <iostream>

#include "Loop.h"

Loop::Loop(SDL_Renderer* p_renderer)
{
	renderer = p_renderer;
}

bool Loop::start()
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

			// Handle event listeners
			for (int i = 0; i < eventListeners.size(); i++)
			{
				eventListeners[i]->handleEvent(e);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Handle render listeners
		handleBeforeRender();
		SDL_RenderPresent(renderer);
		handleAfterRender();
	}
	return true;
}

Loop::~Loop()
{}

// Events
void Loop::addEventListeners(ObjectPointers& listenObjects)
{
	for (int i = 0; i < listenObjects.size(); i++)
	{
		addEventListener(listenObjects[i]);
	}
}

void Loop::removeEventListener(Object* ptr)
{}

// Render
void Loop::addRenderListeners(ObjectPointers& objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		addRenderListener(objects[i]);
	}
}

void Loop::removeRenderListener(Object* ptr)
{}

void Loop::handleBeforeRender()
{
	for (int i = 0; i < renderListeners.size(); i++)
	{
		renderListeners[i]->onBeforeRender();
	}
}

void Loop::handleAfterRender()
{
	for (int i = 0; i < renderListeners.size(); i++)
	{
		renderListeners[i]->onAfterRender();
	}
}