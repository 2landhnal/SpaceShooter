#pragma once
#include <vector>
#include <gl2d/gl2d.h>
#include <singleton.h>
#include <baseObject.h>

class GameManager: public Singleton<GameManager>
{
private:
	friend class Singleton<GameManager>;
	GameManager() {}
public:
	 std::vector<BaseObject*> objects;
	 void Clear();
	 void AddObject(BaseObject* obj);
	 void RemoveObject(BaseObject* obj);
};