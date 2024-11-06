#include <global.h>
#include <string>

void Global::InitSpriteConfig() {
	// health bar
	healthBar.loadFromFile(RESOURCES_PATH "UI/healthBar.png", true);
	health.loadFromFile(RESOURCES_PATH "UI/health.png", true);

	// ship
	playerBlueprint.SetTexture(RESOURCES_PATH "spaceShip/new ships/ship_3.png", 250);
	enemyBlueprint.SetTexture(RESOURCES_PATH "spaceShip/new ships/ship_1.png", 250);

	// bullet
	bulletBlueprint.SetTexture(3, 2, RESOURCES_PATH "spaceShip/stitchedFiles/projectiles.png", 500, 50);
	bulletBlueprint.texturePos = { 0, 1 };

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
}