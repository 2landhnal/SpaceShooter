#pragma once
#include <ctime>
#include <singleton.h>

struct Counter {
	float time;
	float counter;
	Counter(float time) {
		this->time = time;
		this->counter = rand() % (int)time;
	}
};

class GameData : public Singleton<GameData>
{
private:
	friend class Singleton<GameData>;
	GameData() {}
public:
	int score = 0;
	int currentSkinIndex = 0;
	Counter* enemySpawnTime, * itemSpawnCounter, * hpSpawnCounter;
	time_t timestamp;

	inline void Reset() {
		score = 0;
		enemySpawnTime = new Counter(5);
		itemSpawnCounter = new Counter(30);
		hpSpawnCounter = new Counter(30);
		time(&timestamp);
	}
};