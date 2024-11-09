#include <item.h>

class ItemBullet: public Item
{
public:
	void Update(float deltaTime) override;
	void Trigger(SpaceShip* ship) override;
};