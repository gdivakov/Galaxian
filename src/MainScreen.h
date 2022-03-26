#pragma once
#include <SDL.h>

#include "App.h"
#include "Level.h"

class MainScreen : public Level
{
private:
	typedef std::vector<Object*> ObjectPointers;
	bool isActive;
public: 
	MainScreen(const App* p_system);
	virtual void start();
};

// Options: 

// Start game 
// Settings
// Quit 