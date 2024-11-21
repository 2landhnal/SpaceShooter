#include <spaceShip.h>	
#include <global.h>
#include <gameManager.h>
#include <bullet.h>

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

bool SpaceShip::CollideCheck() {
	for (auto& obj : GameManager::GetInstance().objects)
	{
		// check collide with itself
		if (obj == dynamic_cast<BaseObject*>(this)) continue;

		SpaceShip* spaceShipObj = dynamic_cast<SpaceShip*>(this);
		Bullet* bulletObj = dynamic_cast<Bullet*>(obj);
		if (bulletObj && bulletObj->owner == spaceShipObj) continue;

		Damageable* dmgObj = dynamic_cast<Damageable*>(obj);
		SpriteRenderer* spriteRendererObj = dynamic_cast<SpriteRenderer*>(obj);

		if (spriteRendererObj && dmgObj && isCollide(spriteRendererObj))
		{
			dmgObj->TakeDamage(hp);
			TakeDamage(hp);
			return true;;
		}
	}
}

void  SpaceShip::Update(float deltaTime) {
	if (CollideCheck()) {
		return;
	}
}