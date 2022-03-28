#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"
#include "LevelBase.h"
#include "LevelManager.h"

class Level1 : public LevelBase {
private:
	LevelManager* controller;
public: 
	Level1(const App* p_system, LevelManager* p_controller) :
		LevelBase(p_system), controller(p_controller) {};

	virtual void load();
};