#pragma once


class FrameTime
{
private:
	static FrameTime* instance;
	float deltaTime;
	FrameTime();
	~FrameTime();
	
public:
	void setDeltaTime(float dt);
	
	float getDeltaTime();

	static FrameTime* getInstance();

};

