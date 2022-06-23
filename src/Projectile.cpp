#include "Projectile.h"

const int SPEED_DIVIDER = 50;

Projectile::Projectile(
	PJ_Params params,
	ProjectileManager* p_parent
) 
: Collidable(
	p_parent->getShip()->level->getSystem()->getRenderer(),
	getAmmoParamsByGunType(params.gun).collidableType,
	getRadius(params.gun),
	getAmmoParamsByGunType(params.gun).colliders
)
{
	rotation = params.rotation;
	position = params.position;
	direction = params.direction;
	speed = params.speed;
	textures = params.textures;
	selectedTexture = textures.launch;
	parent = p_parent;
	frame = 0;
	isStarted = false;

	shiftColliders();

	// Register it this way to have PJ always on top of other sprites
	parent->getSystem()->getGameLoop()->addRenderListener(this);
	
	// Link collidables
	Collidables enemyCollidables = parent->getShip()->linkedCollidables;

	for (int i = 0; i < enemyCollidables.size(); i++)
	{
		linkTo(enemyCollidables[i]);
	}
}

Projectile::~Projectile()
{

	parent->getSystem()->getGameLoop()->removeRenderListener(this);

	parent = NULL;
	selectedTexture = NULL;
}

void Projectile::selectTexture()
{
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
}

Vector2 Projectile::getNextPos()
{
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

	return nextPos;
}

void Projectile::onBeforeRender()
{
	if (isStarted && !isCollided && !parent->getShip()->level->isPaused)
	{
		move();
	}

	selectTexture();

	Texture::Clips clips = selectedTexture->getClips();
	SDL_Rect* currentClip = &clips[frame / clips.size()];

	Vector2 nextPos = getNextPos();

	selectedTexture->render(nextPos, currentClip, rotation);
}

void Projectile::onAfterRender()
{
	Texture::Clips clips = selectedTexture->getClips();
	int clipsLength = clips.size();

	if (++frame / clipsLength >= clipsLength)
	{
		if (!isStarted)
		{
			isStarted = true;
		}

		if (isCollided)// Collided and exploded
		{
			isActive = false;
		}

		resetAnimation();
	}

	if (isOutside(position) || 
		!isActive || 
		parent->getShip()->level->getIsAccelerated()) // Remove projectiles
	{
		destroyCollidable();
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
	Collidable::rotation = rotation;
};

void Projectile::handleCollided()
{
	Audio* audioPlayer = parent->getSystem()->getAudioPlayer();
	audioPlayer->playSound(PJ_EXPLOSION_SOUND);

	destroyCollidable();
}

void Projectile::destroyCollidable()
{

	unlink();
	resetAnimation();
}

