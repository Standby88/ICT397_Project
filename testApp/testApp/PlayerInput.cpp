#include "PlayerInput.h"


PlayerInput::PlayerInput()
{

	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	lastX = w / 2;
	lastY = h / 2;
	photo = false;
	manual = false;
	wire = false;
	worldDisplay = true;
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
	photo = false;
	manual = false;
	wire = false;
	worldDisplay = true;
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
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

PlayerInput::~PlayerInput()
{
}



void PlayerInput::DoMovement(GLfloat time)
{
	camera = Camera::GetCameraInstance();
	// Camera controls
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_REPEAT)
	{
		camera->ProcessKeyboard(FORWARD, time);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_REPEAT)
	{
		camera->ProcessKeyboard(BACKWARD, time);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_REPEAT)
	{
	camera->ProcessKeyboard(LEFT, time);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_REPEAT)
	{
	camera->ProcessKeyboard(RIGHT, time);
	}

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
}

void PlayerInput::WrapKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	PlayerInput *p = &getCurrentPlayerInput();
	p->KeyCallback(glfwGetCurrentContext(), key, scancode, action, mode);
}

void PlayerInput::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		if (photo == false)
		{
			photo = true;
			worldDisplay = false;
		}
		else if(photo == true)
		{
			glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
		}
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		if (manual == false)
		{
			manual = true;
			worldDisplay = false;
		}
		else if (manual == true)
		{
			manual = false;
			worldDisplay = true;
		}
	}if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		if (wire == false)
		{
			wire = true;
		}
		else if (wire == true)
		{
			wire = false;
		}
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
	camera = Camera::GetCameraInstance();
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
	//if (xOffset > 0.0f || yOffset > 0.0f)
	camera->ProcessMouseMovement(xOffset, yOffset);
}

void PlayerInput::WrapScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	PlayerInput *p = &getCurrentPlayerInput();
	p->ScrollCallback(glfwGetCurrentContext(), xOffset, yOffset);
}

bool PlayerInput::getPhoto()
{
	return photo;
}

bool PlayerInput::getManual()
{
	return manual;
}

bool PlayerInput::getWorldDisplay()
{
	return worldDisplay;
}
bool PlayerInput::getWire()
{
	return wire;
}
void PlayerInput::ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	camera->ProcessMouseScroll(yOffset);
}