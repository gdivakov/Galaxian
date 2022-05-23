#pragma once
#include <SDL.h>

#include "Object.h"
#include "LevelBase.h"
#include "PauseView.h"
#include "MilesView.h"
#include "StatusBarView.h"
#include "BuffBarView.h"
#include "GameOverView.h"

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
	StatusBarView* statusView;
	BuffBarView* buffView;
	GameOverView* gameOverView;

};

