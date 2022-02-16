#include <iostream>
#include <vector>

#include "Timer.h"
#include "Projectile.h"
#include "Consts.h"

//struct Gun
//{
//	GunTypes gun;
//	float cooldownMs;
//	TextureParams texture;
//	Projectile ammo;
//};

class WeaponModule : public Texture
{
public:
	WeaponModule(
		GunTypes initGunType, 
		SDL_Renderer* renderer, 
		SDL_Point* p_shipPosition
	);
	void fire();
	void addGun();
	void removeGun();

	virtual void handleEvent(SDL_Event& e);
	virtual void onBeforeRender();
	virtual void onAfterRender();
	~WeaponModule();
private:
	bool isOnCooldown;
	float cooldownMs;
	GunTypes selectedGun;
	std::vector<GunTypes> availableGuns;
	Timer cooldownTimer;
	SDL_Point* shipPosition;
	Projectile ammo;
};