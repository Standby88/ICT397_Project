#pragma once

#include <iostream>
#include "GameWorld.h"
#include "ScriptEngine.h"
#include "SceneRender.h"
#include "GameController.h"
#include "Window.h"
#include "FrameTime.h"

/**
* @class Graphics engine
* @brief USed to setup openGl and rednering
*
* @author alex
* @version 1
* @date
*
* @todo
*
* @bug
*/
class GameEngine
{
private:
	///GameWorld* variable
	GameWorld* gameWorld;
	///SceneRender* variable
	SceneRender* render;
	///Window variable
	Window window;
	///GameController* variable
	GameController *gameController;
	///PhysicsFacade singleton instance variable
	PhysicsFacade* PhysFac = PhysicsFacade::GetPhysicsInstance();
	///FrameTime variable for delta time
	FrameTime *dt;
	///int variables for screen height and width
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	///GLdouble variable
	GLdouble lastX = SCREEN_WIDTH / 2.0;
	///GLdouble variable
	GLdouble lastY = SCREEN_HEIGHT / 2.0;
	///bool array 
	bool keys[1024];
	///bool variable
	bool firstMouse = true;
	///GLfloat variable
	GLfloat deltaTime = 0.0f;
	///GLfloat variable
	GLfloat lastFrame = 0.0f;

public:

	///Default constructor
	GameEngine();

	///Default destructor
	~GameEngine();

	/**
	* @brief runs game loop, returns true when game loop is exited
	* @param void 
	* @return bool
	*/
	bool GameLoop();

	/**
	* @brief initialises GameEngine's variables
	* @param void 
	* @return void
	*/
	void initialize();


};