#pragma once
#include "MathLib.h"
#include <string>

static float TimeToFrame(float time)
{
	float frame = 0.041666666667;
	return time / frame;
}

//This next function converts from a start frame and an end frame passed in to
//a start time and an end time, both of which are stored in a glm::vec2.
static glm::vec2 FramesToTime(glm::vec2 frames)
{
	float frame = 0.041666666667;
	return frames * frame;
}


class Animation
{
public:
	std::string name;
	float start_time;
	float end_time;
	int priority;
	Animation();
	Animation(std::string in_name, glm::vec2 times, int in_priority);
	~Animation();
};

