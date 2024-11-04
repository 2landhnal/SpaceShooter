#pragma once
#include <gl2d/gl2d.h>
#include "platformInput.h"
#include <baseObject.h>

class InputHandler
{
private:
	glm::vec2 deltaMove = {};
public:
	void Update(float deltaTime);
	glm::vec2 GetDeltaMove();
};