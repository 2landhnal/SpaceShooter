#include <damageable.h>
#include <baseObject.h>

void Damageable::TakeDamage(float amount) {
	hp -= amount;
	if (hp <= 0) {
		Defeat();
	}
}
void Damageable::Defeat() {
	ShowEffect();
	BaseObject* baseObj = dynamic_cast<BaseObject*>(this);
	if (baseObj) {
		baseObj->MarkForDelete();
	}
	else {
		delete this;
	}
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