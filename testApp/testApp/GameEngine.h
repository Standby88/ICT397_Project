#pragma once

#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


#include "GameWorld.h"
#include "ScriptEngine.h"
#include "SceneRender.h"
#include "GameController.h"

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
	GameWorld* gameWorld;
	SceneRender* render;
	GLFWwindow *window;
	GameController *gameController;
	PhysicsFacade* PhysFac = PhysicsFacade::GetPhysicsInstance();

	const GLint WIDTH = 800, HEIGHT = 600;
	int SCREEN_WIDTH, SCREEN_HEIGHT;


	GLdouble lastX = WIDTH / 2.0;
	GLdouble lastY = HEIGHT / 2.0;

	bool keys[1024];
	bool firstMouse = true;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

public:

	GameEngine();
	~GameEngine();
	bool GameLoop();
	void initilize();


};