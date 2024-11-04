#include <spriteRenderer.h>
#include <renderManager.h>
#include <helper.h>


SpriteRenderer::SpriteRenderer() {
    RenderManager::GetInstance().AddObject(this);
}

SpriteRenderer:: ~SpriteRenderer() {
    RenderManager::GetInstance().RemoveObject(this);
}
void SpriteRenderer::SetBlueprint(SpriteBlueprint blueprint) {
	this->blueprint = blueprint;
}

void SpriteRenderer::SetLayer(int l) {
	RenderManager::GetInstance().RemoveObject(this);
	this->blueprint.SetLayer(l);
	RenderManager::GetInstance().AddObject(this);
}

void SpriteRenderer::Render(gl2d::Renderer2D& renderer)
{
	float angle = FromDirectionToAngle(viewDirection);
	if (blueprint.isAtlas)
	{
		renderer.renderRectangle({ position - glm::vec2(blueprint.size / 2,blueprint.size / 2), blueprint.size,blueprint.size },
			blueprint.texture, Colors_White, {}, angle, blueprint.atlas.get(blueprint.texturePos.x, blueprint.texturePos.y));
	}
	else 
	{
		renderer.renderRectangle(
			{ position - glm::vec2(blueprint.size / 2,blueprint.size / 2), blueprint.size,blueprint.size }, 
			blueprint.texture,
			Colors_White, {}, glm::degrees(angle) + 90.f);
	}
}