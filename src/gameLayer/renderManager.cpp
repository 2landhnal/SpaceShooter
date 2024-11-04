#include <renderManager.h>

RenderManager::RenderManager() {
    objects.resize(100);
}
void RenderManager::Clear() {
    for (int i = 0; i < objects.size(); i++) {
        objects[i].clear();
    }
}

void RenderManager::AddObject(SpriteRenderer* obj) {
    if (obj->blueprint.layer > objects.size()) { // Ensure layer is within bounds
        objects.resize(obj->blueprint.layer + 1);
    }
    objects[obj->blueprint.layer].push_back(obj);
}

void RenderManager::RemoveObject(SpriteRenderer* obj) {
    vector<SpriteRenderer*>& layerObjects = objects[obj->blueprint.layer];
    try {
        layerObjects.erase(
            remove(layerObjects.begin(), layerObjects.end(), obj),
            layerObjects.end()
        );
        throw obj->blueprint.layer; // Throw an exception when a problem arise
    }
    catch (int layer) {
        // Block of code to handle errors
    }
}