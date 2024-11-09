#pragma once
#include <gl2d/gl2d.h>
#include <baseObject.h>
#include <spriteRenderer.h>
#include <spaceShip.h>

class Item : public SpriteRenderer, public BaseObject
{
public:
	inline virtual void Update(float deltaTime){}
	inline virtual void Trigger(SpaceShip* ship) {}
};