#pragma once
#include <gl2d/gl2d.h>
#include <baseObject.h>
#include <spriteRenderer.h>

class Bullet:public BaseObject
{
private:
	float speed = 2000.0f;
public:
	SpriteRenderer spriteRenderer;
	void Update(float deltaTime) override;
};