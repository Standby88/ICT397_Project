#pragma once

#include <vector>

#include "PhysicsFacade.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "MathLib.h"


enum Camera_Move
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;


/**
* @class Camera
* @brief Camera class used for viewing the scene
*
*
* @author Alex
* @version
* @date
*
* @todo
*
* @bug
*/

class Camera
{
public:

	/**
	* @brief constructor for camera, initialises all the values
	*
	* @param vec3 position, vec3 up, vec3 yaw, vec3 pitch
	*/
	Camera(V3 position = V3(0.0f, 0.0f, 0.0f), V3 up = V3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW
		, GLfloat pitch = PITCH) : front(V3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
		GLFWwindow* win = glfwGetCurrentContext();
		int x, y;
		glfwGetWindowSize(win, &x, &y);
		glfwSetCursorPos(win, (double)x / 2, (double)y / 2);
		CreateCameraRigidBodyBox();
	}

	/**
	* @brief constructor for camera, initialises all the values
	*
	* @param GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch
	*/
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	/**
	* @brief accessor for view matrix
	*
	* @param
	* @return looAt Matrix
	*/
	M4 GetViewMatrix();

	/**
	* @brief process keyboard input to change camera position
	*
	* @param Camera_Move direction, GLfloat deltaTime
	*/
	void ProcessKeyboard(Camera_Move direction, GLfloat deltaTime);


	static Camera* GetCameraInstance();

	/**
	* @brief process mouse input to change camera pitch and yaw
	*
	* @param GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch
	*/
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);

	/**
	* @brief process mouse scroll input to change camera zoom
	*
	* @param GLfloat yOffset
	*/
	void ProcessMouseScroll(GLfloat yOffset);

	/**
	* @brief accessor for zoom
	*
	* @return zoom
	*/
	GLfloat GetZoom();

	void CreateCameraRigidBodyBox();

private:
	// Camera Attributes
	V3 position;
	V3 front;
	V3 up;
	V3 right;
	V3 worldUp;

	// Eular Angles
	GLfloat yaw;
	GLfloat pitch;

	// Camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;
	
	static Camera* instance;

	PhysicsFacade* cPhysFac = PhysicsFacade::GetPhysicsInstance();

	/**
	* @brief helper function that is used to update the camera when a parameter is changed
	*
	*/
	void updateCameraVectors();

	

};