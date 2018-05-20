#include "Animation.h"



Animation::Animation()
{
	start_time = end_time = priority = 0;
}

Animation::Animation(std::string in_name, glm::vec2 times, int in_priority)
{
	name = in_name;
	start_time = times.x;
	end_time = times.y;
	priority = in_priority;
}


Animation::~Animation()
{
}
