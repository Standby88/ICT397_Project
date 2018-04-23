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
	GLFWwindow *window;
	TerrainManager *Tm;
	EnvironmentObjManager *Eom;
	GameWorld* gameWorld;
	SceneRender* render;
	glm::mat4 projection;
	PlayerInput playerInput;
	GLFWwindow *window;
public:
	/**
	* @brief Constructor for GraphicsEngine
	*/
	GameEngine();

	/**
	* @brief desstructor for GraphicsEngine
	*/
	~GameEngine();

	/**
	* @brief used to set up gl function and game loop
	*/
	bool GLFWpro();

	/// Window dimensions
	const GLint WIDTH = 800, HEIGHT = 600;
	int SCREEN_WIDTH, SCREEN_HEIGHT;

	///static texture
	ModelManager m_Models;
	TextureManager m_TextureMan;

	///scene camera and camera variables
	Camera*  camera = Camera::GetCameraInstance();
	GLdouble lastX = WIDTH / 2.0;
	GLdouble lastY = HEIGHT / 2.0;

	///Physics 
	PhysicsFacade* PhysFac = PhysicsFacade::GetPhysicsInstance();

	///input key states
	bool keys[1024];
	bool firstMouse = true;

	///wire drawing
	bool wire = false;

	///frame rate/game cycle variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	///photo variables
	GLuint VBO, VAO, EBO;
	GLuint texture1 = 0;
	GLuint texture2 = 0;
	void initilize();
	/**
	* @brief used to set up photo for quiting
	*/
	void setupPhoto();

	/**
	* @brief draw exist photo
	*
	*@param shader
	*/
	void drawPhoto(Shader S);

	void setUpmanual();

	void drawMaunal(Shader S);

};