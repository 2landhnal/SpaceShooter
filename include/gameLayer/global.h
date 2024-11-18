#pragma once
#include <vector>
#include <gl2d/gl2d.h>
#include <singleton.h>
#include <spriteBlueprint.h>
#include <raudio.h>

class SpaceShip;

struct AnimationThing {
	std::vector<glm::vec2> cors;
	SpriteBlueprint blueprint;
};

class Global : public Singleton<Global>
{
private:
	friend class Singleton<Global>;
	Global() {}
public:
	std::vector<SpaceShip*> ships; // here
	gl2d::Texture healthBar;
	gl2d::Texture health;
	std::vector <SpriteBlueprint> backGroundBlueprint, upGroundBlueprint;
	// object
	SpriteBlueprint playerBlueprint, enemyBlueprint;
	// bullet
	std::vector< SpriteBlueprint> playerBulletBlueprints = std::vector< SpriteBlueprint>(6);
	std::vector< SpriteBlueprint> enemyBulletBlueprints = std::vector< SpriteBlueprint>(1);
	// fx
	AnimationThing explosionAnim, bulletCollisionAnim;
	// AnimationThing electricAnim;
	// item
	SpriteBlueprint bulletItemBlueprint, hpItemBlueprint;
	// sound
	Sound shootSound, pickItemSound;
	void InitSpriteConfig();
	void SpawnExplosion(glm::vec2 pos);
	void SpawnBulletCollision(glm::vec2 pos);
};