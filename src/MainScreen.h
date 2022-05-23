#pragma once
#include <SDL.h>

#include "App.h"
#include "LevelBase.h"
#include "LevelManager.h"

class MainScreen : public LevelBase
{
private:
	typedef std::vector<Object*> ObjectPointers;
public: 
	MainScreen(const App* p_system, LevelManager* p_controller) :
		LevelBase(p_system, p_controller) {};
	virtual void load();
	virtual void initAudio();
	virtual void accelerate() {};
	void startGame();
}; 