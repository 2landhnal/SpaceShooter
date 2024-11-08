#pragma once
#include <gl2d/gl2d.h>
#include "platformInput.h"
#include <baseObject.h>

class InputHandler: public BaseObject
{
private:
	glm::vec2 deltaMove = {};
public:
	void Update(float deltaTime)  override;
	glm::vec2 GetDeltaMove();
};