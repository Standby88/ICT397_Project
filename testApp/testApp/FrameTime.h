#pragma once


class FrameTime
{
private:
	static FrameTime* instance;
	float deltaTime;
	FrameTime();
	~FrameTime();
	float timeElapsed;
public:
	void setDeltaTime(float dt);
	
	float getDeltaTime();
	
	void setElapsedTime(float time)
	{
		timeElapsed = time;
	}
	float getElapsedTime()
	{
		return timeElapsed;
	}
	static FrameTime* getInstance();

};

