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
            break;
        }
    }
}

void GameManager::RemoveMarkedForDelete() {
    for (auto it = objects.begin(); it != objects.end();) {
        if ((*it)->markForDelete) {
            BaseObject* tmp = *it;
            it = objects.erase(it);
            delete tmp;
        }
        else {
            ++it;
        }
    }
}