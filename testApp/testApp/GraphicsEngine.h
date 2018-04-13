#pragma once

#include <iostream>

// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>

#include "SOIL2\SOIL2.h"
#include "WorldTerrain.h"
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

	///scene camera and camera variables
	Camera  camera;
	GLfloat lastX = WIDTH / 2.0;
	GLfloat lastY = HEIGHT / 2.0;

	///input key states
	bool keys[1024];
	bool firstMouse = true;

	///wire drawing
	bool wire = false;

	///frame rate/game cycle variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;


};

/*void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (keys[GLFW_KEY_M])
	{
		if (!wire) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			wire = true;
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			wire = false;
		}
	}
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

									 //prepare for next frame
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	camera.ProcessMouseScroll(yOffset);
}*/