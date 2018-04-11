#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>


#include "Camera.h"

class PlayerInput
{
public:
	PlayerInput();
	~PlayerInput();

	PlayerInput(int width, int height, Camera *cam, GLfloat *deltaTime);

	GLfloat lastX;
	GLfloat lastY;
	bool keys[1024];
	bool firstMouse = true;

	GLfloat m_time;

	Camera *camera;

	bool wire = false;

	static PlayerInput & getCurrentPlayerInput();
	static void destroyCurrentPlayerInput();

	void DoMovement(GLfloat time);

	static void WrapKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void WrapMouseCallback(GLFWwindow *window, double xPos, double yPos);
	static void WrapScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
private:

	int w, h;

	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	void MouseCallback(GLFWwindow *window, double xPos, double yPos);
	void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
};

