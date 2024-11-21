#include <global.h>
#include <string>
#include <animation.h>
#include <raudio.h>

void Global::InitSpriteConfig() {

	// font
	font.createFromFile(RESOURCES_PATH "/font/operius.ttf");

	// health bar
	healthBar.loadFromFile(RESOURCES_PATH "UI/healthBar.png", true);
	health.loadFromFile(RESOURCES_PATH "UI/health.png", true);

	// ui
	playButton.loadFromFile(RESOURCES_PATH "UI/btn.png", true);

	// item
	bulletItemBlueprint.SetTexture(RESOURCES_PATH "item/bullet.png", 100);
	hpItemBlueprint.SetTexture(RESOURCES_PATH "item/hp.png", 100);

	// explosion
	explosionAnim.blueprint.SetTexture(7, 1, RESOURCES_PATH "/fx/explosion.png", 336, 500);
	bulletCollisionAnim.blueprint.SetTexture(8, 1, RESOURCES_PATH "/fx/bulletCol.png", 256, 200);
	pickItemAnim.blueprint.SetTexture(9, 1, RESOURCES_PATH "/fx/pickItem.png", 576, 300);
	//electricAnim.blueprint.SetTexture(RESOURCES_PATH "bullet/electricBall/1.png", 200);

	// ship
	for (int i = 0; i < playerBlueprints.size(); i++) {
		std::string s = "spaceShip/new ships/ship_" + std::to_string(i + 1) + ".png";
		playerBlueprints[i].SetTexture(RESOURCES_PATH+s, 250);
		playerBlueprints[i].layer = 1;
	}
	enemyBlueprint.SetTexture(2, 2, RESOURCES_PATH "/spaceship/enemy/enemy.png", 96, 250);
	enemyBlueprint.texturePos = { 0, 0 };

	// bullet
	for (int i = 0; i < playerBulletBlueprints.size(); i++) {
		std::string s = "/bullet/p" + std::to_string(i + 1) + ".png";
		playerBulletBlueprints[i].SetTexture(RESOURCES_PATH+s, 100);
	}

	for (int i = 0; i < enemyBulletBlueprints.size(); i++) {
		std::string s = "/bullet/e" + std::to_string(i + 1) + ".png";
		enemyBulletBlueprints[i].SetTexture(RESOURCES_PATH + s, 100);
	}

	// background 
	int bgLayers = 3;
	int bgSize = 4000;
	backGroundBlueprint.resize(bgLayers);
	for (int i = 0; i < bgLayers; i++) {
		std::string  s = "background/bg" + std::to_string(i + 1) + ".png";
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
	enemyBlueprint.layer = 1;
	explosionAnim.blueprint.layer = 2;
	bulletCollisionAnim.blueprint.layer = 2;
	pickItemAnim.blueprint.layer = 2;

	// cors
	for (int i = 0; i < 7; i++) {
		glm::vec2 v = { i, 0 };
		explosionAnim.cors.push_back(v);
	}
	for (int i = 0; i < 8; i++) {
		glm::vec2 v = { i, 0 };
		bulletCollisionAnim.cors.push_back(v);
	}
	for (int i = 0; i < 9; i++) {
		glm::vec2 v = { i, 0 };
		pickItemAnim.cors.push_back(v);
	}
	//for (int i = 1; i < 61; i++) {
	//	glm::vec2 v = { i, 0 };
	//	electricAnim.cors.push_back(v);
	//}

	// sound
	shootSound = LoadSound(RESOURCES_PATH "sfx/shoot2Cutted.wav");
	pickItemSound = LoadSound(RESOURCES_PATH "sfx/item.wav");
	music = LoadSound(RESOURCES_PATH "music/bg.mp3");
	explodeSound = LoadSound(RESOURCES_PATH "sfx/explode.wav");

	SetSoundVolume(music, 0.1);
	SetSoundVolume(pickItemSound, 0.2);
	SetSoundVolume(shootSound, 0.2);
	SetSoundVolume(explodeSound, 0.2);
}

void Global::SpawnExplosion(glm::vec2 pos) {
	//Animation* explosion = new Animation(electricAnim.blueprint, electricAnim.cors, 0.08, false, "bullet/electricBall/", ".png");
	Animation* fx = new Animation(explosionAnim.blueprint, explosionAnim.cors, 0.08, false);
	fx->spriteRenderer.position = pos;
	Sound sound = explodeSound;
	PlaySound(sound);
}

void Global::SpawnBulletCollision(glm::vec2 pos) {
	Animation* fx = new Animation(bulletCollisionAnim.blueprint, bulletCollisionAnim.cors, 0.08, false);
	fx->spriteRenderer.position = pos;
}

void Global::SpawnPickItemFx(glm::vec2 pos) {
	Animation* fx = new Animation(pickItemAnim.blueprint, pickItemAnim.cors, 0.05, false);
	fx->spriteRenderer.position = pos;
}