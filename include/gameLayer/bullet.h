#pragma once
#include <gl2d/gl2d.h>
#include <glm/glm.hpp>
#include <baseObject.h>
#include <spriteRenderer.h>
#include <global.h>

class Bullet:public BaseObject
{
private:
	float speed = 2000.0f;
	float damage = 1;
public:
	float GetDamage();
	SpaceShip* owner; 
	SpriteRenderer spriteRenderer;
	void Update(float deltaTime) override;
	void SetOwner(SpaceShip* spaceShip);
	void Delete();
	bool isCollide(SpaceShip* ship);
};