#include "GameController.h"

GameController::GameController(GameWorld * gw)
{
	PhysFac = PhysicsFacade::GetPhysicsInstance();
	gameWorld = gw;
	camera = Camera::GetCameraInstance();
	
	gameWorld->setProjection(MathLib::perspective(camera->GetZoom(), (float)gameWorld->getScreenW() / (float)gameWorld->getScreenH(), 0.1f, 1000.0f));
	playerInput = PlayerInput::getCurrentPlayerInput();
	playerInput.SetAttributes(camera);
	playerInput.SetCallbacks();
}

GameController::~GameController()
{
	camera = nullptr;
	delete camera;
	gameWorld = nullptr;
	delete gameWorld;
}

void GameController::update(GLfloat deltaTime)
{
	glfwPollEvents();
	playerInput.DoMovement(deltaTime);
	camera = Camera::GetCameraInstance();	//probably don't need this line (kieron)
	gameWorld->setView(camera->GetViewMatrix());
	gameWorld->setPhoto(PlayerInput::getCurrentPlayerInput().getPhoto());
	gameWorld->setManual(PlayerInput::getCurrentPlayerInput().getManual());
	gameWorld->setWorldDisplay(PlayerInput::getCurrentPlayerInput().getWorldDisplay());
	gameWorld->setWire(PlayerInput::getCurrentPlayerInput().getWire());
}
