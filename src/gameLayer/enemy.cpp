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
	glm::vec2 playerPos = Player::GetInstance().position;
	glm::vec2 directionToPlayer = GetLookDirection(position, playerPos);
	glm::vec2 newDirection = {};
	bool shoot = (glm::length(directionToPlayer + viewDirection) >= fireRange);
	if (shoot)
	{
		if (firedTime <= 0.f)
		{
			// Can shoot
			Shoot();
			firedTime = fireTimeReset;
		}
	}
	firedTime -= deltaTime;
	if (firedTime < 0) { firedTime = 0.f; }
	if (glm::length(directionToPlayer + viewDirection) <= 0.2)
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
			deltaTime * turnSpeed * directionToPlayer + viewDirection;
	}
	float length = glm::length(newDirection);
	length = glm::clamp(length, 0.1f, 3.f);
	viewDirection = glm::normalize(newDirection);
	position += (deltaTime * speed * viewDirection * length);
}