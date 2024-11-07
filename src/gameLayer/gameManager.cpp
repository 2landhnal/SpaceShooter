#include <gameManager.h>
#include <typeinfo>

void GameManager::Clear() {
	objects.clear();
}

void GameManager::AddObject(BaseObject* obj) {
    objects.push_back(obj);
}

void GameManager::RemoveObject(BaseObject* obj) {
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (*it == obj) {
            objects.erase(it);
            break; // Exit the loop after erasing to avoid invalid iterator access
        }
    }
}