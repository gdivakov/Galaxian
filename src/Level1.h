#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"
#include "LevelBase.h"
#include "LevelManager.h"
#include "Object.h"

class Level1 : public LevelBase {
private:
	LevelManager* controller;
	void initAudio();
public: 
	Level1(const App* p_system, LevelManager* p_controller) :
		LevelBase(p_system, p_controller) {};

	virtual void load();
};