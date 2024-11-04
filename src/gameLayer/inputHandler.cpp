#include <inputHandler.h>	
#include <player.h>

glm::vec2 InputHandler::GetDeltaMove() {
	return deltaMove;
}
void InputHandler::Update(float deltaTime)
{
	deltaMove = {};
	if (
		platform::isButtonHeld(platform::Button::W) ||
		platform::isButtonHeld(platform::Button::Up)
		)
	{
		deltaMove.y = -1;
	}
	if (
		platform::isButtonHeld(platform::Button::S) ||
		platform::isButtonHeld(platform::Button::Down)
		)
	{
		deltaMove.y = 1;
	}
	if (
		platform::isButtonHeld(platform::Button::A) ||
		platform::isButtonHeld(platform::Button::Left)
		)
	{
		deltaMove.x = -1;
	}
	if (
		platform::isButtonHeld(platform::Button::D) ||
		platform::isButtonHeld(platform::Button::Right)
		)
	{
		deltaMove.x = 1;
	}

	if (deltaMove.x != 0 || deltaMove.y != 0)
	{
		deltaMove = glm::normalize(deltaMove);
		deltaMove *= deltaTime * Player::GetInstance().speed;
		*Player::GetInstance().Position() += deltaMove;
	}

#pragma region handle bulets
	if (platform::isLMousePressed())
	{
		Player::GetInstance().Shoot();
	}
#pragma endregion
}