#include <spaceShip.h>	
#include <helper.h>
#include <global.h>]

glm::vec2* SpaceShip:: Position(){
	return &(spriteRenderer.position);
}
void SpaceShip::Shoot() {
	Bullet* b = new Bullet();
	b->spriteRenderer.SetBlueprint(Global::GetInstance().bulletBlueprint);
	b->spriteRenderer.position = spriteRenderer.position;
	b->spriteRenderer.viewDirection = spriteRenderer.viewDirection;
}

SpaceShip::SpaceShip() {
	name = "Spaceship";
	spriteRenderer.SetLayer(1);
}