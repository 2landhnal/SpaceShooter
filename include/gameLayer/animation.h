#pragma once
#include <gl2d/gl2d.h>
#include <string>
#include <spriteRenderer.h>
#include <baseObject.h>
#include <vector>
#include <string>

class Animation : public BaseObject
{
private:
    float counter;
    int index;
public:
    std::vector<glm::vec2> cors;
    bool loop = false;
    float duration;
    SpriteRenderer spriteRenderer;
    std::string prefix, suffix;

    Animation(SpriteBlueprint blueprint, std::vector<glm::vec2> cors, float duration, bool loop);
    Animation(SpriteBlueprint blueprint, std::vector<glm::vec2> cors, float duration, bool loop, std::string prefix, std::string suffix);
    Animation();
    ~Animation();
    void Update(float deltaTime) override;
    void Destroy();
    std::string GetTexturePath();
};