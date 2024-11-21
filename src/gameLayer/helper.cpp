#include <helper.h>
#include <cmath>

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

float RadiansToDegrees(float radians) {
	float pi = atan(1) * 4;
	return radians * (180.0f / pi);
}

float fromDirectionToDegree(glm::vec2& direction) {
	// Calculate the angle in radians from the x-axis
	float radians = std::atan2(direction.y, direction.x);

	// Convert radians to degrees
	float degrees = RadiansToDegrees(radians);

	// Ensure the angle is between 0 and 360
	if (degrees < 0) {
		degrees += 360.0f;
	}

	return degrees;
}

glm::vec2 GetRotateDirection(glm::vec2& from, float angle) {

	// to radian
	float pi = atan(1) * 4;
	while (angle < 0) {
		angle += 360;
	}
	while (angle > 360) {
		angle -= 360;
	}
	angle = angle * (pi / 180.0f);


	float cosAngle = std::cos(angle);
	float sinAngle = std::sin(angle);

	float x = from.x * cosAngle - from.y * sinAngle;
	float y = from.x * sinAngle + from.y * cosAngle;

	return { x, y };
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

bool isClickOn(glm::vec4& boxCor, int w, int h) {
	if (platform::isLMouseReleased()) {
		glm::vec2 mousePos = platform::getRelMousePosition();
		mousePos.x /= w;
		mousePos.y /= h;
		return (boxCor.x <= mousePos.x && mousePos.x <= (boxCor.x + boxCor.z))
			&& (boxCor.y <= mousePos.y && mousePos.y <= (boxCor.y + boxCor.w));
	}
	return false;
}