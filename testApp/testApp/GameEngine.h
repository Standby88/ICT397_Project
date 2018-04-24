#pragma once

#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "GameWorld.h"
#include "Camera.h"
#include "ScriptEngine.h"
#include "SceneRender.h"
#include "PlayerInput.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "GameAssetFactory.h"

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
	TerrainManager *Tm;
	EnvironmentObjManager *Eom;
	GameWorld* gameWorld;
	SceneRender* render;

	GLFWwindow *window;

	glm::mat4 projection;
	PlayerInput playerInput;

	const GLint WIDTH = 800, HEIGHT = 600;
	int SCREEN_WIDTH, SCREEN_HEIGHT;

	Camera*  camera = Camera::GetCameraInstance();
	GLdouble lastX = WIDTH / 2.0;
	GLdouble lastY = HEIGHT / 2.0;

	PhysicsFacade* PhysFac = PhysicsFacade::GetPhysicsInstance();

	bool wire = false;

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