#include <baseObject.h>
#include <gameManager.h>

BaseObject::BaseObject() {
    markForDelete = false;
    GameManager::GetInstance().AddObject(this);
}
BaseObject::~BaseObject() {
    GameManager::GetInstance().RemoveObject(this);
}

void BaseObject::Update(float deltaTime) {};
void BaseObject::MarkForDelete() {
    markForDelete = true;
}

void BaseObject::Destroy() {
    MarkForDelete();
}