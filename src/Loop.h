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

	void addEventListeners(const ObjectPointers& objects);
	void addEventListener(Object* ptr) { eventListeners.push_back(ptr); };
	void removeEventListener(const Object* ptr);
	void removeEventListeners(const ObjectPointers& objects);

	void addRenderListeners(const ObjectPointers& objects);
	void addRenderListener(Object* ptr) { renderListeners.push_back(ptr); };
	void removeRenderListener(const Object* ptr);
	void removeRenderListeners(const ObjectPointers& objects);

	void handleBeforeRender() const;
	void handleAfterRender() const;
private:
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
};