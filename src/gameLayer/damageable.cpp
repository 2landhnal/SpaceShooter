#include <damageable.h>

void Damageable::TakeDamage(float amount) {
	hp -= amount;
	if (hp < 0) {
		Defeat();
	}
}
void Damageable::Defeat() {
	ShowEffect();
	delete this;
}
void Damageable::ShowEffect() {
	// 
}
void Damageable::Revive() {
	hp = maxHp;
}
Damageable::Damageable() {
	Revive();
}
Damageable::~Damageable() {

}