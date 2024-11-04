#pragma once
#include <gl2d/gl2d.h>

struct SpriteBlueprint {
	char* path;
	gl2d::Texture texture;
	gl2d::TextureAtlasPadding atlas;
	glm::vec2 texturePos = { 1, 1 };
	float size;
	bool isAtlas;
	int layer = 0;
	void SetTexture(int x, int y, char* path, int atlasSize, int size);
	void SetTexture(char* path, int size);
	void SetLayer(int l);
};