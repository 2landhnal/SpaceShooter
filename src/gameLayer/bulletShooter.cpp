#include <bulletShooter.h>
#include <spaceShip.h>
#include <player.h>

BulletShooter::BulletShooter() {
	int size = Global::GetInstance().playerBulletBlueprints.size();
	bulletBlueprint = &(Global::GetInstance().playerBulletBlueprints[rand()%size]);
}

Bullet* BulletShooter::SpawnBullet() {
	Bullet* b = new Bullet();
	b->SetOwner(this->owner);
	if (this->owner != dynamic_cast<SpaceShip*>(&Player::GetInstance())) {
		int size = Global::GetInstance().enemyBulletBlueprints.size();
		bulletBlueprint = &(Global::GetInstance().enemyBulletBlueprints[rand() % size]);
	}
	b->SetBlueprint(*bulletBlueprint);
	b->position = owner->position;
	return b;
}

void BulletShooter::Shoot() {
	Bullet* b = SpawnBullet();
	b->viewDirection = owner->viewDirection;
}

void BulletShooter::SetOwner(SpaceShip* obj) {
	owner = obj;
}