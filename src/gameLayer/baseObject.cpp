#include <baseObject.h>
#include <gameManager.h>

BaseObject::BaseObject() {
    GameManager::GetInstance().AddObject(this);
}
BaseObject::~BaseObject() {
    GameManager::GetInstance().RemoveObject(this);
}

void BaseObject::Update(float deltaTime) {};