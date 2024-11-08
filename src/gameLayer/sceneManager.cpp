#include <sceneManager.h>

SceneManager::SceneManager() {
    StartCounting();
}

void SceneManager::Clear() {
	objects.clear();
}

void SceneManager::AddObject(TimeLogger* obj) {
	objects.push_back(obj);
}

void SceneManager::RemoveObject(TimeLogger* obj) {
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (*it == obj) {
            objects.erase(it);
            break;
        }
    }
}

void SceneManager::Restart() {
    for (auto it = objects.begin(); it != objects.end(); /* no increment here */) {
        if (difftime((*it)->createAt, startAt) > 0) {
            (*it)->MarkDeleted();
            delete* it; // Delete the object
            it = objects.erase(it); // Erase returns the next iterator
        }
        else {
            ++it; // Only increment if you didn’t erase
        }
    }
    StartCounting();
}


void SceneManager::StartCounting() {
	startAt = std::time(0);
}
