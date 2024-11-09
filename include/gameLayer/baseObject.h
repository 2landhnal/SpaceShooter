#pragma once
#include <gl2d/gl2d.h>
#include <string>
#include <timeLogger.h>

class BaseObject : public TimeLogger
{
public:
    std::string name = "Base"; // for debug
    bool markForDelete = false;
    BaseObject();
    ~BaseObject();
	virtual void Update(float deltaTime);
    void MarkForDelete();
    virtual void Destroy();
};