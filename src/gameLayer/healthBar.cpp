#include <healthBar.h>
#include <global.h>

void RenderHealthBar(gl2d::Renderer2D& renderer, Player& player, int w, int h)
{
	renderer.pushCamera();
	{
		float rate = player.hp / player.maxHp;
		glui::Frame f({ 0,0, w, h });
		glui::Box healthBox = glui::Box().xLeftPerc(0.35).yTopPerc(0.85).
			xDimensionPercentage(0.3).yAspectRatio(1.f / 8.f);
		renderer.renderRectangle(healthBox, Global::GetInstance().healthBar);
		glm::vec4 newRect = healthBox();
		newRect.z *= rate;
		glm::vec4 textCoords = { 0,1,1,0 };
		textCoords.z *= rate;
		renderer.renderRectangle(newRect, Global::GetInstance().health, Colors_White, {}, {},
			textCoords);
	}
	renderer.popCamera();
}