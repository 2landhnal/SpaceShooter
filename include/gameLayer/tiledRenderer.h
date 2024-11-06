#pragma once
#include <gl2d/gl2d.h>
#include <baseObject.h>
#include <spriteRenderer.h>

class TiledRenderer: public SpriteRenderer
{
public:
	float paralaxStrength = 1;
	void Render(gl2d::Renderer2D& renderer) override;
};