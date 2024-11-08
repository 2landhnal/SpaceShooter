#include <spaceShip.h>	
#include <global.h>

void SpaceShip::Shoot() {
	Bullet* b = new Bullet();
	b->SetOwner(this);
	b->SetBlueprint(Global::GetInstance().bulletBlueprint);
	b->position = position;
	b->viewDirection = viewDirection;
}

SpaceShip::SpaceShip() {
	name = "Spaceship";
	hp = maxHp;
	Global::GetInstance().ships.push_back(this);
}

SpaceShip::~SpaceShip() {
	auto& ships = Global::GetInstance().ships;
	// Find this spaceship in the ships vector
	auto it = std::find(ships.begin(), ships.end(), this);
	// If found, erase it
	if (it != ships.end()) {
		ships.erase(it);
	}
}

void SpaceShip::ShowEffect() {
	Global::GetInstance().SpawnExplosion(position);
}