#include <item.h>

class ItemHP: public Item
{
private:
	float amount = 1;
public:
	void Update(float deltaTime) override;
	void Trigger(SpaceShip* ship) override;
};