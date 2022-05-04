#pragma once

#include <SDL.h>

#include "Object.h"
#include "LevelBase.h"
#include "PauseView.h"
#include "MilesView.h"
#include "StateView.h"

class PauseView;

class Hood : public Object
{
public:
	Hood(LevelBase* p_level);
	~Hood();
	virtual void handleEvent(SDL_Event& e);
	virtual void onBeforeRender();
	void handlePaused();
	void handleResumed();
private:
	SDL_Renderer* renderer;
	LevelBase* level;
	const App* system;
	PauseView* pauseView;
	MilesView* milesView;
	StateView* stateView;
};

