#pragma once
#include <gl2d/gl2d.h>
#include <string>

class BaseObject
{
public:
    std::string name = "Base"; // for debug
    BaseObject();
    ~BaseObject();
	virtual void Update(float deltaTime);
};