#pragma once
#include <vector>
#include <gl2d/gl2d.h>
#include <singleton.h>
#include <spriteRenderer.h>

using namespace std;

class RenderManager : public Singleton<RenderManager>
{
private:
	friend class Singleton<RenderManager>;
	RenderManager();
public:
	vector<vector<SpriteRenderer*>> objects;
	void Clear();
	void AddObject(SpriteRenderer* obj);
	void RemoveObject(SpriteRenderer* obj);
};