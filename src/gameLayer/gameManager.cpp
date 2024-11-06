#include <gameManager.h>
#include <typeinfo>

void GameManager::Clear() {
	objects.clear();
}

void GameManager::AddObject(BaseObject* obj) {
    objects.push_back(obj);
}

void GameManager::RemoveMarkedObjects() {
    for (auto it = objects.begin(); it != objects.end(); ) {
        if ((*it)->markedForDeletion) {
            //delete* it; // Delete the object
            it = objects.erase(it); // Erase from vector and get the next iterator
        }
        else {
            ++it;
        }
    }
}