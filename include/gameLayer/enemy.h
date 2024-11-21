#pragma once
#include <gl2d/gl2d.h>
#include <spaceShip.h>
class Enemy:public SpaceShip
{
private:
	float turnSpeed = 3.f;
	float firedTime = 1.f;
	float fireTimeReset = 0.2;
	float fireRange = 1.5;
public:
	Enemy();
	void Update(float deltaTime) override;
	void Defeat() override;
};