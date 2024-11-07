#pragma once
#include <gl2d/gl2d.h>
#include <ctime>

class TimeLogger
{
public:
	time_t createAt;
	TimeLogger();
	~TimeLogger();
};