#include <tiledRenderer.h>
void TiledRenderer::Render(gl2d::Renderer2D& renderer)
{
	auto viewRect = renderer.getViewRect();
	glm::vec2 paralaxDistance = { viewRect.x, viewRect.y };
	paralaxDistance *= -paralaxStrength;
	// draw 9 pieces around screen
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{

			// draw 9 bg instances around our ship
			// viewRect = cordinate of center screen view
			int posX = x + int((viewRect.x - paralaxDistance.x) / blueprint.size);
			int posY = y + int((viewRect.y - paralaxDistance.y) / blueprint.size);

			renderer.renderRectangle(
				glm::vec4{posX, posY, 1, 1}*blueprint.size
				+ glm::vec4(paralaxDistance, 0, 0)
				, blueprint.texture);
		}
	}
}