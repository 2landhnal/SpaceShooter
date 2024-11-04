#pragma once
#include <gl2d/gl2d.h>
#include <bullet.h>
#include <baseObject.h>

class SpaceShip: public BaseObject
{
public:
	int speed = 500;  // 500px/s
	float hp = 0.5f;
	SpaceShip();
	SpriteRenderer spriteRenderer;
	glm::vec2* Position();
	void Shoot();
};