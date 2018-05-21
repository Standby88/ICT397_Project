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
static Animation Anim_Test_Walk("Walk", FramesToTime(glm::vec2(1, 45)), 1);
static Animation Anim_Test_Idle("Idle", FramesToTime(glm::vec2(51, 110)), 2);
class GameEngine
{
private:
	GameWorld* gameWorld;
	SceneRender* render;
	Window window;
	GameController *gameController;
	PhysicsFacade* PhysFac = PhysicsFacade::GetPhysicsInstance();
	FrameTime *dt;
	int SCREEN_WIDTH, SCREEN_HEIGHT;


	GLdouble lastX = SCREEN_WIDTH / 2.0;
	GLdouble lastY = SCREEN_HEIGHT / 2.0;

	bool keys[1024];
	bool firstMouse = true;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

public:

	GameEngine();
	~GameEngine();
	bool GameLoop();
	void initialize();


};