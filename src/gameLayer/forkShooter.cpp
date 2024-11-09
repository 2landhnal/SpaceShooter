#include <forkShooter.h>
#include <helper.h>
#include <spaceShip.h>

void ForkShooter::Shoot() {
    Bullet* centerBullet = SpawnBullet();
    if (centerBullet) {
        centerBullet->viewDirection = owner->viewDirection;
    }

    Bullet* rightBullet = SpawnBullet();
    if (rightBullet) {
        rightBullet->viewDirection = GetRotateDirection(owner->viewDirection, 30);
    }

    Bullet* leftBullet = SpawnBullet();
    if (leftBullet) {
        leftBullet->viewDirection = GetRotateDirection(owner->viewDirection, -30);
    }
}