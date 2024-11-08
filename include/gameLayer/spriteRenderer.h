#pragma once
#include <gl2d/gl2d.h>
#include <spriteBlueprint.h>
#include <timeLogger.h>

class SpriteRenderer: public TimeLogger
{
public:
	SpriteBlueprint blueprint;

	glm::vec2 position = { 100,100 };
	glm::vec2 viewDirection = { 1,0 };

	virtual void Render(gl2d::Renderer2D& renderer);
	void SetBlueprint(SpriteBlueprint blueprint);
    SpriteRenderer();
    ~SpriteRenderer();
};