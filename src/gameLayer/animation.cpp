#include <animation.h>

void Animation::Update(float deltaTime) {
	//if (cors.size() == 0) return;
	counter -= deltaTime;
	if (counter < 0) {
		counter = duration;
		index++;
		if (index >= cors.size()) {
			if (loop) {
				index = 0;
			}
			else {
				Destroy();
				return;
			}
		}
		if (spriteRenderer.blueprint.isAtlas) {
			spriteRenderer.blueprint.texturePos = cors[index];
		}
		else {
			spriteRenderer.blueprint.SetTexture(GetTexturePath().c_str(), spriteRenderer.blueprint.size);
		}
	}
}

std::string Animation::GetTexturePath() {
	std::string s = prefix + std::to_string((int)cors[index].x) + suffix;
	s = RESOURCES_PATH + s;
	return s;
}

void Animation::Destroy() {
	delete this;
}

Animation::Animation(SpriteBlueprint blueprint, std::vector<glm::vec2> cors, float duration, bool loop) {
	this->spriteRenderer.SetBlueprint(blueprint);
	this->cors = cors;
	this->duration = duration;
	this->loop = loop;
	counter = duration;
	index = 0;
}
Animation::Animation(SpriteBlueprint blueprint, std::vector<glm::vec2> cors, float duration, bool loop, std::string prefix, std::string suffix) {
	this->spriteRenderer.SetBlueprint(blueprint);
	this->cors = cors;
	this->duration = duration;
	this->loop = loop;
	this->prefix = prefix;
	this->suffix = suffix;
	counter = duration;
	index = 0;
}

Animation::Animation() {
	counter = duration;
	index = 0;
}

Animation::~Animation() {

}