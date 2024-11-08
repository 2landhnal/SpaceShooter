#pragma once
#include <gl2d/gl2d.h>
#include <timeLogger.h>
#include <singleton.h>
#include <ctime>

class SceneManager : public Singleton<SceneManager>
{
private:
	friend class Singleton<SceneManager>;
	SceneManager();
public:
	time_t startAt;
	std::vector<TimeLogger*> objects;

	void StartCounting();
	void Clear();
	void AddObject(TimeLogger* obj);
	void RemoveObject(TimeLogger* obj);
	void Restart();
};