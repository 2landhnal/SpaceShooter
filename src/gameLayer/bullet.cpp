#include <bullet.h>	
#include <player.h>

void Bullet::Update(float deltaTime)
{
	spriteRenderer.position += spriteRenderer.viewDirection * deltaTime * speed;

	if (glm::distance(spriteRenderer.position, Player::GetInstance().spriteRenderer.position) > 5'000)
	{
		this->Delete();
	}
}