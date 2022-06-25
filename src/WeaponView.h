#pragma once
#include "Texture.h"
#include "LevelBase.h"

class WeaponView
{
public:
	WeaponView(LevelBase* p_level);
	~WeaponView();
	void handleRender();
private:
	LevelBase* level;
	Texture* selectedGunBar;
	GunType selectedGun;

	bool isFirstInit;
	void loadSelectedGunBar();
};

