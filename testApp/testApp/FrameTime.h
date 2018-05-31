#pragma once

/**
* @class FrameTime
* @brief Used to encapsulate delta time and elapsed time
*
* @author yik Jun Desmond ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
class FrameTime
{
private:
	///static FrameTime* variable
	static FrameTime* instance;
	///float variable for delta time
	float deltaTime;
	///float variablefor elapsed time
	float timeElapsed;

	///Default Constructor
	FrameTime();

	///Default Destructor
	~FrameTime();

public:

	/**
	* @brief sets delta time
	* @param float 
	* @return void
	*/
	void setDeltaTime(float dt);
	
	/**
	* @brief returns delta time
	* @param void
	* @return float
	*/
	float getDeltaTime();
	
	/**
	* @brief sets elapsed time
	* @param float 
	* @return void 
	*/
	void setElapsedTime(float time)
	{
		timeElapsed = time;
	}

	/**
	* @brief returns elapsed time
	* @param void
	* @return float
	*/
	float getElapsedTime()
	{
		return timeElapsed;
	}

	/**
	* @brief returns a static instance of FrameTime
	* @param void
	* @return static FrameTime*
	*/
	static FrameTime* getInstance();

};

