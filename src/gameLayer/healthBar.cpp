#include <healthBar.h>
#include <global.h>
#include <math.h>

void HealthBar::RenderHealthBar(gl2d::Renderer2D& renderer, int w, int h)
{
		glui::Frame f({ 0,0, w, h });
		glui::Box healthBox = glui::Box().xLeftPerc(0.35).yTopPerc(0.85).
			xDimensionPercentage(0.3).yAspectRatio(1.f / 8.f);
		renderer.renderRectangle(healthBox, Global::GetInstance().healthBar);
		glm::vec4 newRect = healthBox();
		newRect.z *= cur;
		glm::vec4 textCoords = { 0,1,1,0 };
		textCoords.z *= cur;
		renderer.renderRectangle(newRect, Global::GetInstance().health, Colors_White, {}, {},
			textCoords);
}

void HealthBar::Update(float deltaTime) {
	float rate = Player::GetInstance().hp / Player::GetInstance().maxHp;
	if (abs(cur-rate) > acceptable) {
		int dir = cur > rate ? 1 : -1;
		cur -= deltaTime * dir * speed * abs(cur - rate);
	}
}