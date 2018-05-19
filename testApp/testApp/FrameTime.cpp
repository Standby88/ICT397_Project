#include "FrameTime.h"

FrameTime * FrameTime::instance = 0;

FrameTime::FrameTime()
{
	deltaTime = 0;
}

FrameTime::~FrameTime()
{
	instance = nullptr;
	delete instance;
}

void FrameTime::setDeltaTime(float dt)
{
	deltaTime = dt;
}

float FrameTime::getDeltaTime()
{
	return deltaTime;
}

FrameTime * FrameTime::getInstance()
{
	if (instance == 0)
	{
		instance = new FrameTime();
	}
	return instance;
}