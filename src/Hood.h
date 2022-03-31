#pragma once

#include <SDL.h>

#include "Object.h"
#include "LevelBase.h"
#include "PauseView.h"

class Hood : public Object
{
public:
	Hood(SDL_Renderer* p_renderer, LevelBase* p_level, const App* p_system);
	~Hood();
	virtual void handleEvent(SDL_Event& e);
	virtual void onBeforeRender();
private:
	SDL_Renderer* renderer;
	LevelBase* level;
	const App* system;
	PauseView* pauseView;
};

