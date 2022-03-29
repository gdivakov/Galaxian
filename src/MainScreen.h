#pragma once
#include <SDL.h>

#include "App.h"
#include "LevelBase.h"
#include "LevelManager.h"

class MainScreen : public LevelBase
{
private:
	typedef std::vector<Object*> ObjectPointers;
	LevelManager* controller;
public: 
	MainScreen(const App* p_system, LevelManager* p_controller) :
		LevelBase(p_system), controller(p_controller) {};
	virtual void load();
	void startGame();
	//void openSettings();
	void quit();
}; 