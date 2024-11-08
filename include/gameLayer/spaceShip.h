#pragma once
#include <gl2d/gl2d.h>
#include <helper.h>
#include <bullet.h>
#include <baseObject.h>
#include <damageable.h>

class SpaceShip: public BaseObject, public Damageable, public SpriteRenderer
{
public:
	int speed = 500;  // 500px/s
	void Shoot();
	void ShowEffect() override;
	SpaceShip();
	~SpaceShip();
};