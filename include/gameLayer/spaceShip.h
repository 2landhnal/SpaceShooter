#pragma once
#include <gl2d/gl2d.h>
#include <helper.h>
#include <bullet.h>
#include <baseObject.h>

class SpaceShip: public BaseObject
{
public:
	int speed = 500;  // 500px/s
	float maxHp = 5;
	float hp = 1;
	SpriteRenderer spriteRenderer;
	glm::vec2* Position();
	void Shoot();
	virtual void TakeDamage(float amount);
	virtual void Defeat();
	void Delete() override;
	void Revive();
	SpaceShip();
};