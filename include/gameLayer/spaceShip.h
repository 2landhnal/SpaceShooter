#pragma once
#include <gl2d/gl2d.h>
#include <helper.h>
#include <bullet.h>
#include <baseObject.h>
#include <damageable.h>
#include <bulletShooter.h>

class SpaceShip: public BaseObject, public Damageable, public SpriteRenderer
{
public:
	BulletShooter* shooter;
	int speed = 500;  // 500px/s
	void Shoot();
	void ShowEffect() override;
	void Update(float deltaTime) override;
	virtual bool CollideCheck();
	virtual void SetShooter(BulletShooter* newShooter);
	SpaceShip();
	~SpaceShip();
};