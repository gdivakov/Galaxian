#include "BuffBarView.h"
#include "Texture.h"
#include "Ship.h"

BuffBarView::BuffBarView(LevelBase* p_level)
{
	level = p_level;
};


BuffBarView::~BuffBarView()
{
	level = NULL;

	for (BuffSprites::iterator i = sprites.begin(); i != sprites.end(); i++)
	{
		delete i->second;
	}

	sprites.clear();
}

void BuffBarView::handleRender() // Load and render available buffs
{
	Ship* player = level->getPlayer();

	if (!player)
	{
		return;
	}

	std::map<std::string, BuffParams>* playerBuffs = player->getSpecials()->buff->getBuffs();

	int shift = 0;

	for (BuffModule::Buffs::iterator i = playerBuffs->begin(); i != playerBuffs->end(); i++)
	{
		std::string key = i->first;

		if (!sprites[key])
		{
			sprites[key] = new Texture(level->getSystem()->getRenderer());
			sprites[key]->loadFromFile(i->second.sprite.path);
		}

		sprites[key]->render(Vector2(level->getSystem()->getWindowSize()->w - sprites[key]->size.w - 16, shift + level->getSystem()->getWindowSize()->h / 4));

		shift += 40;
	}

}