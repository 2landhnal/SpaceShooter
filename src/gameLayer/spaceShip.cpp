#include <spaceShip.h>	
#include <global.h>

void SpaceShip::Shoot() {
	shooter->Shoot();
}

SpaceShip::SpaceShip() {
	name = "Spaceship";
	hp = maxHp;
	shooter = new BulletShooter();
	shooter->SetOwner(this);
	Global::GetInstance().ships.push_back(this);
}

void SpaceShip::SetShooter(BulletShooter* newShooter) {
	shooter = newShooter;
	shooter->SetOwner(this);
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