#include <itemBullet.h>
#include <gameManager.h>
#include <player.h>
#include <forkShooter.h>
#include <doubleShooter.h>
#include <columnShooter.h>
#include <circleShooter.h>

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
	Sound sound = Global::GetInstance().pickItemSound;
	PlaySound(sound);
	int index = rand()%4;
	switch (index) {
	case 0:
		Player::GetInstance().SetShooter(new CircleShooter());
		break;
	case 1:
		Player::GetInstance().SetShooter(new DoubleShooter());
		break;
	case 2:
		Player::GetInstance().SetShooter(new ForkShooter());
		break;
	case 3: 
		Player::GetInstance().SetShooter(new ColumnShooter());
		break;
	default:
		break;
	}
	Destroy();
}