#include <forkShooter.h>
#include <helper.h>
#include <spaceShip.h>

void ForkShooter::Shoot() {
    SpawnBullet()->viewDirection = GetRotateDirection(owner->viewDirection, -30);
    SpawnBullet()->viewDirection = GetRotateDirection(owner->viewDirection, 0);
    SpawnBullet()->viewDirection = GetRotateDirection(owner->viewDirection, 30);
}