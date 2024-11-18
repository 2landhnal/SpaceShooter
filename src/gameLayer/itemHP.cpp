#include <itemHP.h>
#include <gameManager.h>
#include <player.h>
#include <forkShooter.h>

void ItemHP::Update(float deltaTime)
{
	Player* player = dynamic_cast<Player*>(&Player::GetInstance());
	if (glm::distance(position, player->position) > 5'000)
	{
		Destroy();
	}

	SpriteRenderer* spriteRendererObj = dynamic_cast<SpriteRenderer*>(player);
	if (isCollide(spriteRendererObj))
	{
		SpaceShip* spaceShipObj = dynamic_cast<SpaceShip*>(player);
		Trigger(spaceShipObj);
	}
}

void ItemHP::Trigger(SpaceShip* ship)
{
	Sound sound = Global::GetInstance().pickItemSound;
	PlaySound(sound);
	int index = rand() % 5;
	Player::GetInstance().TakeDamage(-amount);
	Destroy();
}