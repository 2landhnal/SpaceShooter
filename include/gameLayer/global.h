#pragma once
#include <vector>
#include <gl2d/gl2d.h>
#include <singleton.h>
#include <spriteBlueprint.h>

class SpaceShip;

class Global : public Singleton<Global>
{
private:
	friend class Singleton<Global>;
	Global() {}
public:
	std::vector<glm::vec2> explosionCors, bulletCollisonCors;
	std::vector<SpaceShip*> ships; // here
	gl2d::Texture healthBar;
	gl2d::Texture health;
	std::vector <SpriteBlueprint> backGroundBlueprint, upGroundBlueprint;
	SpriteBlueprint playerBlueprint, enemyBlueprint, bulletBlueprint;
	SpriteBlueprint explosionBlueprint, bulletCollisionBlueprint;
	void InitSpriteConfig();
	void SpawnExplosion(glm::vec2 pos);
	void SpawnBulletCollision(glm::vec2 pos);
};