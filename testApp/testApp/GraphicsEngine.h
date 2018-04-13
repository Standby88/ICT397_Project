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

#include "PlayerInput.h"

#include "SOIL2\SOIL2.h"

#include "ModelManager.h"


class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool GLFWpro();


	// Window dimensions
	const GLint WIDTH = 800, HEIGHT = 600;
	int SCREEN_WIDTH, SCREEN_HEIGHT;

	ModelManager m_Models;

	Camera  camera;
	GLdouble lastX = WIDTH / 2.0;
	GLdouble lastY = HEIGHT / 2.0;
	bool keys[1024];
	bool firstMouse = true;

	bool wire = false;

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;


};