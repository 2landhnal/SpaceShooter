#include <spaceShip.h>	
#include <global.h>

glm::vec2* SpaceShip:: Position(){
	return &(spriteRenderer.position);
}
void SpaceShip::Shoot() {
	Bullet* b = new Bullet();
	b->SetOwner(this);
	b->spriteRenderer.SetBlueprint(Global::GetInstance().bulletBlueprint);
	b->spriteRenderer.position = spriteRenderer.position;
	b->spriteRenderer.viewDirection = spriteRenderer.viewDirection;
}

SpaceShip::SpaceShip() {
	name = "Spaceship";
	hp = maxHp;
	Global::GetInstance().ships.push_back(this);
}

void SpaceShip::Delete() {
	auto& ships = Global::GetInstance().ships;
	// Find this spaceship in the ships vector
	auto it = std::find(ships.begin(), ships.end(), this);
	// If found, erase it
	if (it != ships.end()) {
		ships.erase(it);
	}
	BaseObject::Delete();
	spriteRenderer.Delete();
}

void SpaceShip::Defeat() {
	Delete();
}

void SpaceShip::Revive() {
	hp = maxHp;
}

void SpaceShip::TakeDamage(float amount) {
	hp -= amount;
	if (hp <= 0) {
		Defeat();
	}
}