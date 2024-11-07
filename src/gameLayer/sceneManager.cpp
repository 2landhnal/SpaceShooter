#include <sceneManager.h>

void SceneManager::Clear() {
	objects.clear();
}

void SceneManager::AddObject(TimeLogger* obj) {
	objects.push_back(obj);
}

void SceneManager::StartCounting() {
	startAt = std::time(0);
}
