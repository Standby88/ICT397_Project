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
const GLfloat SPEED = 25.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;


/**
* @class Camera
* @brief Camera class used for viewing the scene
*
*
* @author Alex
* @version 1
* @date
*
* @author Kieron van der Kwast
* @version 2
* @date 1/05/2018, Added set and get methods for position of camera, also
					implemented a static function so that only one camera 
					instance is created.
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
		CreateCameraRigidBody();
	}

	/**
	* @brief constructor for camera, initialises all the values
	*
	* @param GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch
	*/
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	/**
	* @brief returns the camera's position coordinates
	*
	* @param void
	* @return V3&
	*/
	V3& GetCameraPosition();

	/**
	* @brief sets the camera's position coordinates
	*
	* @param V3
	* @return void
	*/
	void SetCameraPosition(V3 pos)	{position = pos;};

	/**
	* @brief accessor for view matrix
	*
	* @param
	* @return lookAt Matrix
	*/
	M4 GetViewMatrix();

	/**
	* @brief process keyboard input to change camera position
	*
	* @param Camera_Move direction, GLfloat deltaTime
	*/
	void ProcessKeyboard(Camera_Move direction, GLfloat deltaTime);

	/**
	* @brief returns a singleton instance of Camera class
	*
	* @param void
	* @return Camera*
	*/
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

	/**
	* @brief Creates a rigid body for camera
	*
	* @param void
	* @return void
	*/
	void CreateCameraRigidBody();

	/**
	* @brief flips the pitch of the camera
	* @param void
	* @return void
	*/
	void flipPitch()
	{
		pitch = -pitch;
		updateCameraVectors();
	}

private:

	// Camera Attributes
	///position vector
	V3 position;
	///front vector
	V3 front;
	///up vector
	V3 up;
	///right vector
	V3 right;
	///worldUp vector
	V3 worldUp;

	// Eular Angles
	///GLfloat variable for yaw
	GLfloat yaw;
	///GLfloat variable for pitch
	GLfloat pitch;

	// Camera options
	///GLfloat variable for movement speed
	GLfloat movementSpeed;
	///Glfloat variable for mouse sensitivity
	GLfloat mouseSensitivity;
	///GLfloat variable for zoom
	GLfloat zoom;
	///static Camera* variable 
	static Camera* instance;
	///PhysicsFacade* variable
	PhysicsFacade* cPhysFac = PhysicsFacade::GetPhysicsInstance();
	///rigidBody* variable
	rigidBody* camBody;

	/**
	* @brief helper function that is used to update the camera when a parameter is changed
	*
	*/
	void updateCameraVectors();

};