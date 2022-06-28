#pragma once
#include <map>

#include "LevelBase.h"
#include "SpecialsConsts.h"
#include "Texture.h"

class BuffBarView
{
public:
	typedef std::map<std::string, Texture*> BuffSprites;

	BuffBarView(LevelBase* p_level);
	~BuffBarView();
	void handleRender();
private:
	LevelBase* level;

	BuffSprites sprites;
};

