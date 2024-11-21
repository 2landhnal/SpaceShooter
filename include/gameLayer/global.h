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
	float playerHp=5, enemyHp=2;
	gl2d::Font font;
	glm::vec4 playButtonCor = {0.35, 0.7, 0.3, 0.15};
	glm::vec4 menuButtonCor = { 0.35, 0.7, 0.3, 0.15 };
	glm::vec4 prevCor = { 0.15, 0.7, 0.15, 0.15 };
	glm::vec4 nextCor = { 0.7, 0.7, 0.15, 0.15 };
	std::vector<SpaceShip*> ships; // here
	gl2d::Texture healthBar;
	gl2d::Texture health;
	gl2d::Texture playButton;
	std::vector <SpriteBlueprint> backGroundBlueprint, upGroundBlueprint;
	// object
	std::vector< SpriteBlueprint> playerBlueprints = std::vector<SpriteBlueprint>(14);
	SpriteBlueprint enemyBlueprint;
	// bullet
	std::vector< SpriteBlueprint> playerBulletBlueprints = std::vector< SpriteBlueprint>(6);
	std::vector< SpriteBlueprint> enemyBulletBlueprints = std::vector< SpriteBlueprint>(1);
	// fx
	AnimationThing explosionAnim, bulletCollisionAnim, pickItemAnim;
	// AnimationThing electricAnim;
	// item
	SpriteBlueprint bulletItemBlueprint, hpItemBlueprint;
	// sound
	Sound shootSound, pickItemSound, music, explodeSound;
	void InitSpriteConfig();
	void SpawnExplosion(glm::vec2 pos);
	void SpawnBulletCollision(glm::vec2 pos);
	void SpawnPickItemFx(glm::vec2 pos);
};