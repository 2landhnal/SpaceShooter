#include <spriteBlueprint.h>

void SpriteBlueprint::SetTexture(int x, int y, std::string path, int atlasSize, int size)
{
	isAtlas = true;
	this->size = size;
	texture.loadFromFileWithPixelPadding(path.c_str(), atlasSize, true);
	atlas = gl2d::TextureAtlasPadding(3, 2, texture.GetSize().x, texture.GetSize().y);
}

void SpriteBlueprint::SetTexture(std::string path, int size)
{
	isAtlas = false;
	this->size = size;
	texture.loadFromFile(path.c_str(), true);
}

void SpriteBlueprint::SetTexture(int x, int y, char* path, int atlasSize, int size)
{
	isAtlas = true;
	this->size = size;
	texture.loadFromFileWithPixelPadding(path, atlasSize, true);
	atlas = gl2d::TextureAtlasPadding(3, 2, texture.GetSize().x, texture.GetSize().y);
}

void SpriteBlueprint::SetTexture(char* path, int size)
{
	isAtlas = false;
	this->size = size;
	texture.loadFromFile(path, true);
}