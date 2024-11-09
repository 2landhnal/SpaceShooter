#include <itemBullet.h>
#include <gameManager.h>
#include <player.h>
#include <forkShooter.h>

void ItemBullet::Update(float deltaTime) 
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

void ItemBullet::Trigger(SpaceShip* ship) 
{
	int index = rand() % 5;
	Player::GetInstance().SetShooter(new ForkShooter());
	Destroy();
}