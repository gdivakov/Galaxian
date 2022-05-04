#include "Projectile.h"

int getRadius(GunType type);
bool isOutside(Vector2 pos);
const int SPEED_DIVIDER = 50;

Projectile::Projectile(
	const App* p_system, 
	Vector2 initPosition,
	Ship* p_ship,
	GunType gunType,
	int p_speed,
	PJ_Textures& p_textures,
	ProjectileManager* p_parent
) 
: Collidable(
	p_system->getRenderer(),
	getAmmoParamsByGunType(gunType).colliders, 
	getAmmoParamsByGunType(gunType).collidableType,
	getRadius(gunType)
),
textures(p_textures)
{
	ship = p_ship;
	frame = 0;
	rotation = ship->getRotation();
	position = initPosition;
	direction = ship->getDirection(LOCAL, false);
	isStarted = false;
	system = p_system;
	speed = p_speed;
	parent = p_parent;
	selectedTexture = textures.launch;

	shiftColliders();

	// Register it this way to have PJ always on top of other sprites
	system->getGameLoop()->addRenderListener(this);
	
	std::vector<Collidable*> enemyCollidables = ship->getEnemyCollidables();

	for (int i = 0; i < enemyCollidables.size(); i++)
	{
		registerEnemyCollidable(enemyCollidables[i]);
	}
}

Projectile::~Projectile()
{
	Loop* gameLoop = system->getGameLoop();

	gameLoop->removeRenderListener(this);

	system = NULL;
	ship = NULL;
	parent = NULL;
	selectedTexture = NULL;
}

void Projectile::onBeforeRender()
{
	if (isStarted && !isCollided && !ship->level->isPaused)
	{
		move();
	}

	// Update selected texture if needed
	if (!isStarted)
	{
		selectedTexture = textures.launch;
	}
	else if (isCollided)
	{
		selectedTexture = textures.explosion;
	}
	else
	{
		selectedTexture = textures.flying;
	}

	Texture::Clips clips = selectedTexture->getClips();
	int clipsLength = clips.size();

	SDL_Rect* currentClip = &clips[frame / clipsLength];

	Vector2 center(selectedTexture->getWidth() / 2, selectedTexture->getHeight() / 2);
	Vector2 nextPos = position - center;

	if (isCollided)
	{
		// Explode above the enemy object
		nextPos = 
			position +
			Vector2::getRotatedVector(direction, rotation) -
			Vector2(selectedTexture->getWidth() / 2, 0);
	}

	selectedTexture->render(nextPos, currentClip, rotation);

	if (++frame / clipsLength >= clipsLength)
	{
		if (!isStarted)
		{
			isStarted = true;
		}

		if (isCollided)
		{
			// Collided and exploded
			isActive = false;
		}

		// Renew animation
		frame = 0;
	}
}

void Projectile::onAfterRender()
{
	int explosionClipsSize = textures.explosion->getClips().size();

	if (isOutside(position) || !isActive) // Remove projectiles
	{
		parent->destroyProjectile(this);
	}
}

void Projectile::move()
{
	Vector2 rotatedDir = Vector2::getRotatedVector(direction, rotation);
	position = position + rotatedDir * speed / SPEED_DIVIDER;

	shiftColliders();
	checkCollision();
}

void Projectile::shiftColliders() {
	wrapperCollider.pos = position;
	collidableRotation = rotation;
};

void Projectile::handleCollided()
{
	if (!collidedTo->getIsActive())
	{
		ship->deregisterEnemyCollidable(collidedTo); // Deregister enemy collidable from the parent ship

		// As long as it has "one to many" relation this is correct (game ends when player dies)
		// Otherwise refactor to prevent leaks (all the listeners of the collidedTo should be updated)
	}

	destroyCollidable();
}

void Projectile::destroyCollidable()
{
	deregisterEnemyCollidable(collidedTo); // Deregister enemy collidable from the projectile
	frame = 0;
}

int getRadius(GunType type)
{
	AmmoParams params = getAmmoParamsByGunType(type);
	return params.texture.imageH > params.texture.imageW ? params.texture.imageH / 2 : params.texture.imageW / 2;
}

bool isOutside(Vector2 pos)
{
	bool isOutside = pos.y < 0
		|| pos.x < 0
		|| pos.y > WINDOWED_HEIGHT
		|| pos.x > WINDOWED_WIDTH;

	return isOutside;
};
