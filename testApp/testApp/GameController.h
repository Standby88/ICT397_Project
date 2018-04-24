#pragma once
#include "GameWorld.h"
#include "Camera.h"
#include "PlayerInput.h"
#include <iostream>
class GameController
{
private:
	Camera*  camera;
	GameWorld* gameWorld;
	PlayerInput playerInput;
public:
	GameController(GameWorld* gw);
	~GameController();

	void update(GLfloat deltaTime);
};

