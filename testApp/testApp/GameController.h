#pragma once
#include "GameWorld.h"
#include "Camera.h"
#include "PlayerInput.h"
#include <iostream>

/**
* @class GameController
* @brief
*
* @author Des (I assume)
* @version 1
* @date
*
* @author Kieron
* @version 2
* @date 26/04/2018, Added a PhysicsFacade instance object to access Physics methods.
*
* @todo
*
* @bug
*/
class GameController
{
private:

	Camera*  camera;

	GameWorld* gameWorld;

	PlayerInput playerInput;

	PhysicsFacade* PhysFac;

public:

	GameController(GameWorld* gw);

	~GameController();

	void update(GLfloat deltaTime);
};

