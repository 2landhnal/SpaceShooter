#pragma once
#include <gl2d/gl2d.h>
#include "platformInput.h"

glm::vec2 GetLookDirection(glm::vec2& from, glm::vec2& to);
glm::vec2 GetRotateDirection(glm::vec2& from, float angle);
float GetLookAngle(glm::vec2& from, glm::vec2& to);
float FromDirectionToAngle(glm::vec2& direction);
float fromDirectionToDegree(glm::vec2& direction);
float RadiansToDegrees(float radians);