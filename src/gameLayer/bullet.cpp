#include <bullet.h>	
#include <player.h>
#include <gameManager.h>

void Bullet::Update(float deltaTime)
{
	position += viewDirection * deltaTime * speed;

	if (glm::distance(position, Player::GetInstance().position) > 5'000)
	{
		this->Explode();
	}

	if (owner != nullptr) {
		for (auto& obj : GameManager::GetInstance().objects)
		{
			// bullet itself
			if (obj == dynamic_cast<BaseObject*>(this)) continue;

			// owner check
			BaseObject* baseOwner = dynamic_cast<BaseObject*>(owner);
			if (baseOwner == obj) continue;

			Bullet* bulletObj = dynamic_cast<Bullet*>(obj);
			if (bulletObj && bulletObj->owner == this->owner) continue;

			Damageable* dmgObj = dynamic_cast<Damageable*>(obj);
			SpriteRenderer* spriteRendererObj = dynamic_cast<SpriteRenderer*>(obj);

			if (spriteRendererObj && dmgObj && isCollide(spriteRendererObj))
			{
				dmgObj->TakeDamage(damage);
				Explode();
				break;
			}
		}
	}
}

bool Bullet::isCollide(SpriteRenderer* col)
{
	return glm::distance(position, col->position) <= col->blueprint.size;
}

void Bullet::SetOwner(SpaceShip* spaceShip) {
	owner = spaceShip;
}

float Bullet::GetDamage() {
	return damage;
}

void Bullet::Explode()
{
	ShowEffect();
	Destroy();
}

void Bullet::ShowEffect()
{
	Global::GetInstance().SpawnBulletCollision(position);
}

Bullet::Bullet() {
	maxHp = 1;
	Revive();
}

Bullet::~Bullet() {

}