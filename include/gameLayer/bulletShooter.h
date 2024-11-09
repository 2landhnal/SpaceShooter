#pragma once
#include <gl2d/gl2d.h>
#include <spriteBlueprint.h>
#include <bullet.h>

class SpaceShip;

class BulletShooter
{
protected:
	SpriteBlueprint* bulletBlueprint;
	Bullet* SpawnBullet();
	SpaceShip* owner;
public:
	BulletShooter();
	virtual void Shoot();
	void SetOwner(SpaceShip* obj);
};