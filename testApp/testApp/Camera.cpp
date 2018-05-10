#include "Camera.h"

Camera* Camera::instance = 0;

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
	:front(V3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
{
	this->position = V3(posX, posY, posZ);
	this->worldUp = V3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}

V3& Camera::GetCameraPosition()
{
	return position;
}

Camera* Camera::GetCameraInstance()
{
	if (instance == 0) {
		instance = new Camera(V3(0.0f, 1.75f, 3.0f));
		std::cout << "First camera instance created" << std::endl;
	}

	return instance;
}

M4 Camera::GetViewMatrix()
{
	V3 a= this->position + this->front;
	return MathLib::lookAt(this->position, a, this->up);
}

void Camera::ProcessKeyboard(Camera_Move direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;

	if (direction == FORWARD)
	{
		this->position.x += this->front.x * velocity;
		this->position.z += this->front.z * velocity;
		this->position.y += this->front.y * velocity;
	}

	if (direction == BACKWARD)
	{
		this->position.x -= this->front.x * velocity;
		this->position.z -= this->front.z * velocity;
	}

	if (direction == LEFT)
	{
		this->position -= this->right * velocity;
	}

	if (direction == RIGHT)
	{
		this->position += this->right * velocity;
	}
}

void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	//std::cout<< yOffset << std::endl;
	static bool justwarped = false;
	if (justwarped)
	{
		justwarped = false;
		return;
	}
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	this->yaw += xOffset;
	this->pitch += yOffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	//constrainPitch = false;
	if (constrainPitch)
	{
		if (this->pitch > 89.0f)
		{
			this->pitch = 89.0f;
		}

		if (this->pitch < -89.0f)
		{
			this->pitch = -89.0f;
		}
	}
	

	// Update Front, Right and Up Vectors using the updated Eular angle
	this->updateCameraVectors();

	justwarped = true;
}

void Camera::ProcessMouseScroll(GLfloat yOffset)
{
	if (this->zoom >= 1.0f && this->zoom <= 45.0f)
	{
		this->zoom -= yOffset;
	}

	if (this->zoom <= 1.0f)
	{
		this->zoom = 1.0f;
	}

	if (this->zoom >= 45.0f)
	{
		this->zoom = 45.0f;
	}
}

GLfloat Camera::GetZoom()
{
	return this->zoom;
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	V3 front;
	front.x = cos(MathLib::radians(this->yaw)) * cos(MathLib::radians(this->pitch));
	front.y = sin(MathLib::radians(this->pitch));
	front.z = sin(MathLib::radians(this->yaw)) * cos(MathLib::radians(this->pitch));
	//std::cout <<" unormal "<< front.x << " " << front.y << " " << front.z << std::endl;
	this->front = MathLib::normalize(front);
	// Also re-calculate the Right and Up vector
	this->right = MathLib::normalize(MathLib::cross(this->front, this->worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->up = MathLib::normalize(MathLib::cross(this->right, this->front));
}

void Camera::CreateCameraRigidBody()
{
	camBody = cPhysFac->CreatePlayerRigidBody(1.5, 1.75, 60, position, glm::vec3(0, 0, 0));
	std::cout << "rigidBodyID for Camera: " << camBody->getUserIndex() << std::endl;
}