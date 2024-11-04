#include <helper.h>


glm::vec2 GetLookDirection(glm::vec2& from, glm::vec2& to)
{
	glm::vec2 direction = to - from;
	if (glm::length(direction) == 0.f)
	{
		direction = { 1,0 };
	}
	else
	{
		direction = normalize(direction);
	}
	return direction;
}

float GetLookAngle(glm::vec2& from, glm::vec2& to)
{
	glm::vec2 direction = GetLookDirection(from, to);
	return atan2(direction.y, -direction.x);
}

float FromDirectionToAngle(glm::vec2& direction)
{
	return atan2(direction.y, -direction.x);
}