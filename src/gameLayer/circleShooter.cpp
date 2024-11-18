#include <circleShooter.h>
#include <helper.h>
#include <spaceShip.h>
#include <chrono>

void CircleShooter::Shoot() {
    for (int i = 0; i < 360; i+=30) {
        SpawnBullet()->viewDirection = GetRotateDirection(owner->viewDirection, i);
    }
}