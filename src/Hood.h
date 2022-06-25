#pragma once
#include <SDL.h>

#include "Object.h"
#include "LevelBase.h"
#include "PauseView.h"
#include "MilesView.h"
#include "StatusBarView.h"
#include "BuffBarView.h"
#include "GameOverView.h"
#include "TotalView.h"
#include "WeaponView.h"

class LevelBase;
class PauseView;
class MilesView;
class StatusBarView;
class BuffBarView;
class GameOverView;
class TotalView;
class WeaponView;

class Hood : public Object
{
public:
	Hood(LevelBase* p_level);
	~Hood();

	void handlePaused();
	void handleResumed();
	void showTotal();

	virtual void handleEvent(SDL_Event& e);
	virtual void onBeforeRender();
	virtual void onAfterRender();
private:
	SDL_Renderer* renderer;
	LevelBase* level;
	const App* system;

	PauseView* pauseView;
	MilesView* milesView;
	StatusBarView* statusView;
	BuffBarView* buffView;
	GameOverView* gameOverView;
	TotalView* totalView;
	WeaponView* weaponView;
};

