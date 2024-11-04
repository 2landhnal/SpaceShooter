#include <gameManager.h>

void GameManager::Clear() {
	objects.clear();
}

void GameManager::AddObject(BaseObject* obj) {
    objects.push_back(obj);
}

void GameManager::RemoveMarkedObjects() {
    for (auto it = objects.begin(); it != objects.end(); ) {
        if ((*it)->markedForDeletion) { // still hit here when debug
            //delete* it; // Delete the object
            it = objects.erase(it); // Erase from vector and get the next iterator
        }
        else {
            ++it;
        }
    }
}