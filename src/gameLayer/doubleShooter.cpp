#include <doubleShooter.h>
#include <helper.h>
#include <spaceShip.h>

void DoubleShooter::Shoot() {
    float pow = 50;
    Bullet* tmp = SpawnBullet();
    tmp->viewDirection = owner->viewDirection;
    tmp->position = tmp->position + GetRotateDirection(tmp->viewDirection, 90)*pow;
    tmp = SpawnBullet();
    tmp->viewDirection = owner->viewDirection;
    tmp->position = tmp->position - GetRotateDirection(tmp->viewDirection, 90)*pow;
}