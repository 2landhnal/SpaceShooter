#pragma once
#include <gl2d/gl2d.h>
#include <ctime>

class TimeLogger
{
private:
	bool isDeleted;
public:
	time_t createAt;
	void MarkDeleted();
	TimeLogger();
	virtual ~TimeLogger();
};