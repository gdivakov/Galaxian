#pragma once
#include <SDL.h>

#include "App.h"
#include "LevelBase.h"
#include "LevelManager.h"
#include "SelectShipView.h"
#include "ControlPanel.h"

class ControlPanel;

class MainScreen : public LevelBase
{
private:
	typedef std::vector<Object*> ObjectPointers;
public: 
	MainScreen(const App* p_system, LevelManager* p_controller) :
		LevelBase(p_system, p_controller) 
	{
		initAudio();
	};
	~MainScreen();
	virtual void load();
	virtual void accelerate() {};
	void startGame();
	virtual void handleTick() {};
private:
	SelectShipView* selectShipView = NULL;
	ControlPanel* panel = NULL;
protected:
	virtual void initAudio();
}; 