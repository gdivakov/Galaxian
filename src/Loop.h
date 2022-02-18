#pragma once
#include <SDL.h>
#include <vector>
#include "Object.h"

class Loop {
public: 
	typedef std::vector<Object*> ObjectPointers;

	Loop(SDL_Renderer* p_renderer);
	~Loop();
	bool start();

	void addEventListeners(ObjectPointers& objects);
	void addEventListener(Object* ptr) { eventListeners.push_back(ptr); };
	void removeEventListener(Object* ptr);

	void addRenderListeners(ObjectPointers& objects);
	void addRenderListener(Object* ptr) { renderListeners.push_back(ptr); };
	void removeRenderListener(Object* ptr);

	void handleBeforeRender();
	void handleAfterRender();
private:
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
};