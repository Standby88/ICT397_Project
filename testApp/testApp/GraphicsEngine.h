#pragma once

#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


#include "Camera.h"
#include "Model.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ScriptEngine.h"
#include "SceneRender.h"
#include "PlayerInput.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "GameAssetFactory.h"
#include "EnvironmentObjManager.h"


/*void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();*/
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
class GraphicsEngine
{
public:
	/**
	* @brief Constructor for GraphicsEngine
	*/
	GraphicsEngine();

	/**
	* @brief desstructor for GraphicsEngine
	*/
	~GraphicsEngine();

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
	Camera  camera;
	GLdouble lastX = WIDTH / 2.0;
	GLdouble lastY = HEIGHT / 2.0;

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

};