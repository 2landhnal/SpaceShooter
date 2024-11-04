#pragma once
#include <gl2d/gl2d.h>
#include <string>

class BaseObject
{
public:
    std::string name = "Base"; // for debug
    bool markedForDeletion = false;
    void Delete();
    BaseObject();
	virtual void Update(float deltaTime);
};