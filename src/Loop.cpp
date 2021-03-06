#include <iostream>

#include "Loop.h"

Loop::Loop(SDL_Renderer* p_renderer)
{
	quit = false;
	renderer = p_renderer;
}

bool Loop::start()
{
	quit = false;
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

bool Loop::stop()
{
	quit = true;
	return quit;
}

Loop::~Loop()
{
	renderer = NULL;
}

// Events
void Loop::addEventListeners(const ObjectPointers& listenObjects)
{
	for (int i = 0; i < listenObjects.size(); i++)
	{
		addEventListener(listenObjects[i]);
	}
}

void Loop::removeEventListener(const Object* ptr)
{
	auto removeIter = remove(eventListeners.begin(), eventListeners.end(), ptr);
	eventListeners.erase(removeIter, eventListeners.end());
}

void Loop::removeEventListeners()
{
	eventListeners.clear();
};

// Render
void Loop::addRenderListeners(const ObjectPointers& objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		addRenderListener(objects[i]);
	}
}

void Loop::removeRenderListener(const Object* ptr)
{
	auto removeIter = remove(renderListeners.begin(), renderListeners.end(), ptr);
	renderListeners.erase(removeIter, renderListeners.end());
}

void Loop::removeRenderListeners()
{
	renderListeners.clear();
}

void Loop::handleBeforeRender() const 
{
	for (int i = 0; i < renderListeners.size(); i++)
	{
		renderListeners[i]->onBeforeRender();
	}
}

void Loop::handleAfterRender() const 
{
	for (int i = 0; i < renderListeners.size(); i++)
	{
		renderListeners[i]->onAfterRender();
	}
}