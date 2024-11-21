#pragma once
#include <gl2d/gl2d.h>
#include <player.h>
#include <glui/glui.h>
#include <baseObject.h>

class HealthBar: public BaseObject
{
	float cur = 0;
	float speed = 10;
	float acceptable = 0.001;
public:
	void Update(float deltaTime) override;
	void RenderHealthBar(gl2d::Renderer2D& renderer, int w, int h);
};