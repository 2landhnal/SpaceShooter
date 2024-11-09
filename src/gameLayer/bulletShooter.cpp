#include <bulletShooter.h>
#include <spaceShip.h>

BulletShooter::BulletShooter() {
	bulletBlueprint = &(Global::GetInstance().bulletBlueprint);
}

Bullet* BulletShooter::SpawnBullet() {
	Bullet* b = new Bullet();
	b->SetOwner(this->owner);
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