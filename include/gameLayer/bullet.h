#pragma once
#include <gl2d/gl2d.h>
#include <glm/glm.hpp>
#include <baseObject.h>
#include <spriteRenderer.h>
#include <global.h>
#include <damageable.h>

class Bullet:public BaseObject, public Damageable, public SpriteRenderer
{
private:
	float speed = 2000.0f;
	float damage = 1;
public:
	Bullet();
	~Bullet();
	float GetDamage();
	SpaceShip* owner; 
	void SetOwner(SpaceShip* spaceShip);
	void Explode();

	// baseObj
	void Update(float deltaTime) override;
	// damagable
	void ShowEffect() override;
};