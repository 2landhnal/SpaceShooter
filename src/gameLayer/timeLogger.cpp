#include <timeLogger.h>
#include <sceneManager.h>

TimeLogger::TimeLogger() {
	isDeleted = false;
	createAt = std::time(0);
	SceneManager::GetInstance().AddObject(this);
}
TimeLogger::~TimeLogger() {
	if(!isDeleted) SceneManager::GetInstance().RemoveObject(this);
}
void TimeLogger::MarkDeleted() {
	isDeleted = true;
}
