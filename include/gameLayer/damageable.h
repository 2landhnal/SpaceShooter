#pragma once
#include <gl2d/gl2d.h>
#include <spriteRenderer.h>

class Damageable
{
public:
	float maxHp = 5;
	float hp = 1;

	virtual void TakeDamage(float amount);
	virtual void Defeat();
	virtual void Revive();
	virtual void ShowEffect();
	Damageable();
	virtual ~Damageable();
};