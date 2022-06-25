#include "WeaponView.h"
#include "Ship.h"
#include "ShipConsts.h"
#include <map>

const std::map<GunType, std::string> gunPathByType
{
	{ BLAST, "res/images/blast_bar.png" },
	{ BLAST_DOUBLE, "res/images/blast_double.png" },
	{ BLAST_DIFFUSER, "res/images/diffuser.png" },
};

WeaponView::WeaponView(LevelBase* p_level)
{
	level = p_level;
	selectedGunBar = nullptr;

	isFirstInit = true;
}

WeaponView::~WeaponView()
{
	delete selectedGunBar;

	selectedGunBar = nullptr;
	level = nullptr;
}

void WeaponView::loadSelectedGunBar()
{
	Ship* player = level->getPlayer();

	if (player == nullptr || 
		(!isFirstInit && player->getGun()->getSelectedGun() == selectedGun))
	{
		return;
	}

	// Load new gun
	if (selectedGunBar != nullptr)
	{
		delete selectedGunBar;
	}

	GunType gunType = player->getGun()->getSelectedGun();

	selectedGunBar = new Texture(level->getSystem()->getRenderer());
	selectedGunBar->loadFromFile(gunPathByType.at(gunType));

	selectedGun = gunType;
	isFirstInit = false;
}

void WeaponView::handleRender()
{
	loadSelectedGunBar();

	if (selectedGunBar == nullptr)
	{
		return;
	}

	selectedGunBar->render(Vector2(0, WINDOWED_HEIGHT - selectedGunBar->size.h - 14));
}