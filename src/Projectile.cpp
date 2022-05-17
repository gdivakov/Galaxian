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
	getAmmoParamsByGunType(gunType).collidableType,
	getRadius(gunType),
	getAmmoParamsByGunType(gunType).colliders
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
	
	Collidables enemyCollidables = ship->linkedCollidables;

	for (int i = 0; i < enemyCollidables.size(); i++)
	{
		linkTo(enemyCollidables[i]);
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
	parent = NULL;
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

	if (isCollided && collidedTo->type == COLLIDABLE_SHIP)
	{
		// Explode above the enemy ship
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
		destroyCollidable();
		parent->destroyProjectile(this);
	}
}

void Projectile::move()
{
	Vector2 rotatedDir = Vector2::getRotatedVector(direction, rotation);

	position = position + rotatedDir * speed / SPEED_DIVIDER;

	if (ship->getIsAccelerated())
	{
		Vector2 addVel = Vector2(0, BG_SCROLLING_SPEED_ACCELERATED);
		position += addVel;
	}

	shiftColliders();
	checkCollision();
}

void Projectile::shiftColliders() {
	wrapperCollider.pos = position;
	Collidable::rotation = rotation;
};

void Projectile::handleCollided()
{
	Audio* audioPlayer = system->getAudioPlayer();
	audioPlayer->playSound(PJ_EXPLOSION_SOUND);

	destroyCollidable();
}

void Projectile::destroyCollidable()
{
	unlinkFrom();
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
