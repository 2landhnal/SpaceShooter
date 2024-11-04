#pragma once
#include <gl2d/gl2d.h>
#include <spriteBlueprint.h>

class SpriteRenderer
{
public:
	SpriteBlueprint blueprint;

	glm::vec2 position = { 100,100 };
	glm::vec2 viewDirection = { 1,0 };

	void Render(gl2d::Renderer2D& renderer);
	void SetBlueprint(SpriteBlueprint blueprint);
	void SetLayer(int l);
    SpriteRenderer();
    virtual ~SpriteRenderer();
};