#pragma once
#include <gl2d/gl2d.h>
#include <string>
#include <spriteRenderer.h>
#include <baseObject.h>
#include <vector>

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

    Animation();
    ~Animation();
    void Update(float deltaTime) override;
    void Destroy();
};