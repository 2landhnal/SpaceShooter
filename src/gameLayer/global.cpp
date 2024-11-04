#include <global.h>

void Global::InitSpriteConfig() {
	playerBlueprint.SetTexture(RESOURCES_PATH "spaceShip/new ships/ship_3.png", 250);
	enemyBlueprint.SetTexture(RESOURCES_PATH "spaceShip/new ships/ship_1.png", 250);
	bulletBlueprint.SetTexture(3, 2, RESOURCES_PATH "spaceShip/stitchedFiles/projectiles.png", 500, 50);
	bulletBlueprint.texturePos = { 0, 1 };

	// health bar
	healthBar.loadFromFile(RESOURCES_PATH "UI/healthBar.png", true);
	health.loadFromFile(RESOURCES_PATH "UI/health.png", true);
}