#pragma once
#include <SDL.h>
#include <vector>
#include "Object.h"

class Level;

class Loop {
public: 
	typedef void(*RenderHandler)(Level* level);

	Loop(SDL_Renderer* p_renderer);
	~Loop();
	bool start(RenderHandler onBeforeRender, RenderHandler onAfterRender, Level* level);
	void addListener(Object* listenObject);
	void addListeners(std::vector<Object*>& listenObjects);
	void removeListener();
private:
	SDL_Renderer* renderer;
	std::vector<Object*> listeners;
};