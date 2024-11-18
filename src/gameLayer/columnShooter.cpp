#include <columnShooter.h>
#include <helper.h>
#include <spaceShip.h>

void ColumnShooter::Shoot() {
    SpawnBullet()->viewDirection = owner->viewDirection;
}