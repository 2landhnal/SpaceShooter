#include <global.h>
#include <string>
#include <animation.h>

void Global::InitSpriteConfig() {
	// health bar
	healthBar.loadFromFile(RESOURCES_PATH "UI/healthBar.png", true);
	health.loadFromFile(RESOURCES_PATH "UI/health.png", true);

	// item
	bulletItemBlueprint.SetTexture(RESOURCES_PATH "item/bullet.png", 100);
	hpItemBlueprint.SetTexture(RESOURCES_PATH "item/hp.png", 100);

	// explosion
	explosionBlueprint.SetTexture(7, 1, RESOURCES_PATH "/fx/explosion.png", 336, 500);
	bulletCollisionBlueprint.SetTexture(8, 1, RESOURCES_PATH "/fx/bulletCol.png", 256, 200);

	// ship
	playerBlueprint.SetTexture(RESOURCES_PATH "spaceShip/new ships/ship_3.png", 250);
	enemyBlueprint.SetTexture(2, 2, RESOURCES_PATH "/spaceship/enemy/enemy.png", 96, 250);
	enemyBlueprint.texturePos = { 0, 0 };

	// bullet
	bulletBlueprint.SetTexture(RESOURCES_PATH "/bullet/projectile_2.png", 100);

	// background 
	int bgLayers = 3;
	int bgSize = 4000;
	backGroundBlueprint.resize(bgLayers);
	for (int i = 0; i < bgLayers; i++) {
		std::string  s = "background/bg"+ std::to_string(i+1) + ".png";
		s = RESOURCES_PATH + s;
		// from string to const char*
		backGroundBlueprint[i].SetTexture(s.c_str(), bgSize);
		backGroundBlueprint[i].layer = 0;
	}

	// upground
	int ugLayers = 1;
	int ugSize = 4000;
	upGroundBlueprint.resize(ugLayers);
	for (int i = 0; i < ugLayers; i++) {
		std::string s = "upground/ug" + std::to_string(i + 1) + ".png";
		s = RESOURCES_PATH + s;
		upGroundBlueprint[i].SetTexture(s.c_str(), ugSize);
		upGroundBlueprint[i].layer = 10;
	}

	// layer
	playerBlueprint.layer = 1;
	enemyBlueprint.layer = 1;
	explosionBlueprint.layer = 2;

	// other
	for (int i = 0; i < 7; i++) {
		glm::vec2 v = {i, 0};
		explosionCors.push_back(v);
	}
	for (int i = 0; i < 8; i++) {
		glm::vec2 v = { i, 0 };
		bulletCollisonCors.push_back(v);
	}
}

void Global::SpawnExplosion(glm::vec2 pos) {
	Animation* explosion = new Animation();
	explosion->duration = 0.08;
	explosion->loop = false;
	
	explosion->cors = explosionCors;
	explosion->spriteRenderer.SetBlueprint(explosionBlueprint);
	explosion->spriteRenderer.position = pos;
}

void Global::SpawnBulletCollision(glm::vec2 pos) {
	Animation* explosion = new Animation();
	explosion->duration = 0.08;
	explosion->loop = false;

	explosion->cors = bulletCollisonCors;
	explosion->spriteRenderer.SetBlueprint(bulletCollisionBlueprint);
	explosion->spriteRenderer.position = pos;
}