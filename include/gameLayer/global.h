#pragma once
#include <vector>
#include <gl2d/gl2d.h>
#include <singleton.h>
#include <spriteBlueprint.h>

class Global : public Singleton<Global>
{
private:
	friend class Singleton<Global>;
	Global() {}
public:
	gl2d::Texture healthBar;
	gl2d::Texture health;
	SpriteBlueprint playerBlueprint, enemyBlueprint, bulletBlueprint;
	void InitSpriteConfig();
};