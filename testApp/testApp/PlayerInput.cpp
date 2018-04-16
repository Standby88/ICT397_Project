#include "PlayerInput.h"



PlayerInput::PlayerInput()
{

	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	lastX = w / 2;
	lastY = h / 2;

	m_time = glfwGetTime();

}

PlayerInput::PlayerInput(int width, int height, Camera *cam, GLfloat* deltaTime)
{
	w = width;
	h = height;
	lastX = width / 2;
	lastY = height / 2;
	camera = cam;
	m_time = *deltaTime;
}

void PlayerInput::destroyCurrentPlayerInput()
{
	PlayerInput *playerInput = &getCurrentPlayerInput();
	if(playerInput != NULL)
		delete playerInput;
}

PlayerInput & PlayerInput::getCurrentPlayerInput()
{
	static PlayerInput *playerInput = NULL;

	if (playerInput == NULL) {

		/*glfwSetKeyCallback(glfwGetCurrentContext(), *WrapKeyCallback);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), *WrapMouseCallback);
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);*/

		playerInput = new PlayerInput();
	}

	return *playerInput;
}


void PlayerInput::SetAttributes(Camera *cam)
{
	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	lastX = w / 2;
	lastY = h / 2;

	m_time = glfwGetTime();

	*keys = new bool[1024];

	firstMouse = true;

	camera = cam;
}

void PlayerInput::SetCallbacks()
{
	glfwSetKeyCallback(glfwGetCurrentContext(), *WrapKeyCallback);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), *WrapMouseCallback);
	//glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

PlayerInput::~PlayerInput()
{
}



void PlayerInput::DoMovement(GLfloat time)
{
	// Camera controls
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_REPEAT)
	{
		//std::cout << "GAMEPLAY - W or UP - at TIME - "<< time << std::endl;
		camera->ProcessKeyboard(FORWARD, time);
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_REPEAT)
	{
		//std::cout << "GAMEPLAY - S or DOWN" << std::endl;
		camera->ProcessKeyboard(BACKWARD, time);
	}

	/*if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
	camera->ProcessKeyboard(LEFT, m_time);
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
	camera->ProcessKeyboard(RIGHT, m_time);
	}*/

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_V) == GLFW_PRESS)
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

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
	}
}

void PlayerInput::WrapKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	PlayerInput *p = &getCurrentPlayerInput();
	p->KeyCallback(glfwGetCurrentContext(), key, scancode, action, mode);
}

void PlayerInput::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
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

void PlayerInput::WrapMouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	PlayerInput *p = &getCurrentPlayerInput();
	p->MouseCallback(glfwGetCurrentContext(), xPos, yPos);
}

void PlayerInput::MouseCallback(GLFWwindow *window, double xPos, double yPos)
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

	camera = &Camera::getCameraInstance();

	if (xOffset > 0.0f || yOffset > 0.0f)
		camera->ProcessMouseMovement(xOffset, yOffset);
}

void PlayerInput::WrapScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	PlayerInput *p = &getCurrentPlayerInput();
	p->ScrollCallback(glfwGetCurrentContext(), xOffset, yOffset);
}

void PlayerInput::ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	camera->ProcessMouseScroll(yOffset);
}