#include <enemy.h>
#include <player.h>
#include <helper.h>

Enemy::Enemy()
{
	name = "Enemy";
	speed += rand() % 1000;
	turnSpeed += (rand() & 1000) / 500.f;
	fireRange += (rand() % 1000) / 2000.f;
	fireTimeReset += (rand() % 1000) / 500;
}

void Enemy::Update(float deltaTime)
{
	glm::vec2 playerPos = Player::GetInstance().spriteRenderer.position;
	glm::vec2 directionToPlayer = GetLookDirection(spriteRenderer.position, playerPos);
	glm::vec2 newDirection = {};
	bool shoot = (glm::length(directionToPlayer + spriteRenderer.viewDirection) >= fireRange);
	if (shoot)
	{
		if (firedTime <= 0.f)
		{
			//we can shoot
			Shoot();
			firedTime = fireTimeReset;
		}
	}
	firedTime -= deltaTime;
	if (firedTime < 0) { firedTime = 0.f; }
	if (glm::length(directionToPlayer + spriteRenderer.viewDirection) <= 0.2)
	{
		if (rand() % 2)
		{
			newDirection = glm::vec2(directionToPlayer.y, -directionToPlayer.x);
		}
		else
		{
			newDirection = glm::vec2(-directionToPlayer.y, directionToPlayer.x);
		}
	}
	else
	{
		newDirection =
			deltaTime * turnSpeed * directionToPlayer + spriteRenderer.viewDirection;
	}
	float length = glm::length(newDirection);
	length = glm::clamp(length, 0.1f, 3.f);
	spriteRenderer.viewDirection = glm::normalize(newDirection);
	spriteRenderer.position += (deltaTime * speed * spriteRenderer.viewDirection * length);
}