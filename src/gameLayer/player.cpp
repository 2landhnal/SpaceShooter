#include <player.h>
#include <helper.h>

Player::Player(){
    name = "Player";
    speed *= 1.5f;
}

void Player::Update(float deltaTime) {
    /*glm::vec2 v = { 1, 1 };
    *Position() += v;*/
#pragma region mouse pos
    int w = 0; int h = 0;
    w = platform::getFrameBufferSizeX(); //window w
    h = platform::getFrameBufferSizeY(); //window h

    glm::vec2 mousePos = platform::getRelMousePosition();
    glm::vec2 centerScreen = { w / 2.f, h / 2.f };
    spriteRenderer.viewDirection = GetLookDirection(centerScreen, mousePos);
#pragma endregion
}

Player& Player::GetInstance(){
    static Player instance;
    return instance;
}