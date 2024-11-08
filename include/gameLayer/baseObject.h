#pragma once
#include <gl2d/gl2d.h>
#include <string>
#include <timeLogger.h>

class BaseObject : public TimeLogger
{
public:
    std::string name = "Base"; // for debug
    BaseObject();
    ~BaseObject();
	virtual void Update(float deltaTime);
};