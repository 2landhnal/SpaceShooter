#include <bullet.h>	
#include <player.h>

void Bullet::Update(float deltaTime)
{
	spriteRenderer.position += spriteRenderer.viewDirection * deltaTime * speed;

	if (glm::distance(spriteRenderer.position, Player::GetInstance().spriteRenderer.position) > 5'000)
	{
		this->Delete();
	}

	for (auto&ship : Global::GetInstance().ships)
	{
		if (ship == owner) continue;
		if (isCollide(ship))
		{
			ship->TakeDamage(damage);
			Delete();
			break;
		}
	}
}

bool Bullet::isCollide(SpaceShip* ship)
{
	return glm::distance(spriteRenderer.position, *ship->Position()) <= ship->spriteRenderer.blueprint.size;
}

void Bullet::SetOwner(SpaceShip* spaceShip) {
	owner = spaceShip;
}

float Bullet::GetDamage() {
	return damage;
}

void Bullet::Delete()
{
	BaseObject::Delete();
	spriteRenderer.Delete();
}