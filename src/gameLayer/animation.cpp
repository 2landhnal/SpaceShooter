#include <animation.h>

void Animation::Update(float deltaTime) {
	counter -= deltaTime;
	if (counter < 0) {
		counter = duration;
		index++;
		if (index == cors.size()) {
			if (loop) {
				index = 0;
			}
			else {
				Destroy();
				return;
			}
		}
		spriteRenderer.blueprint.texturePos = cors[index];
	}
}

void Animation::Destroy() {
	delete this;
}

Animation::Animation() {
	counter = duration;
	index = 0;
}

Animation::~Animation() {

}