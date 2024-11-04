#pragma once
#include <gl2d/gl2d.h>
#include "platformInput.h"

glm::vec2 GetLookDirection(glm::vec2& from, glm::vec2& to);
float GetLookAngle(glm::vec2& from, glm::vec2& to);
float FromDirectionToAngle(glm::vec2& direction);