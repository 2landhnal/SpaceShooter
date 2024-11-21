#include <player.h>
#include <forkShooter.h>
#include "platformInput.h"

Player::Player(){
    name = "Player";
    maxHp = Global::GetInstance().playerHp;
    // SetShooter(new ForkShooter());
}

void Player::Defeat() {
    // not doing any thing
}

bool Player::CollideCheck() {
    return false;
}

void Player::Update(float deltaTime) {
    SpaceShip::Update(deltaTime);
#pragma region mouse pos
    int w = 0; int h = 0;
    w = platform::getFrameBufferSizeX(); //window w
    h = platform::getFrameBufferSizeY(); //window h

    glm::vec2 mousePos = platform::getRelMousePosition();
    glm::vec2 centerScreen = { w / 2.f, h / 2.f };
    viewDirection = GetLookDirection(centerScreen, mousePos);
#pragma endregion
}

Player& Player::GetInstance(){
    static Player instance;
    return instance;
}