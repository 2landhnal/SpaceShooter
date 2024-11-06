#include <baseObject.h>
#include <gameManager.h>

BaseObject::BaseObject() {
    markedForDeletion = false;
    GameManager::GetInstance().AddObject(this);
}

void BaseObject::Update(float deltaTime) {};
void BaseObject::Delete() {
    markedForDeletion = true;
}