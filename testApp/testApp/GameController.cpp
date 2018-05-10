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

	//need to create a function that recursively does this for all objects.
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_1")->GetRigidBody());
	/*PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_2")->GetRigidBody());
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_3")->GetRigidBody());
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_4")->GetRigidBody());
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_5")->GetRigidBody());
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_6")->GetRigidBody());
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_7")->GetRigidBody());
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_8")->GetRigidBody());
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("asteroid_9")->GetRigidBody());
	PhysFac->AddRigidBody(gameWorld->getEnvironment()->getObject("Astroboy_1")->GetRigidBody());*/
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
	//std::cout << "cam height" << Camera::GetCameraInstance()->GetCameraPosition().y;
	gameWorld->setPhoto(PlayerInput::getCurrentPlayerInput().getPhoto());
	gameWorld->setManual(PlayerInput::getCurrentPlayerInput().getManual());
	gameWorld->setWorldDisplay(PlayerInput::getCurrentPlayerInput().getWorldDisplay());
	gameWorld->setWire(PlayerInput::getCurrentPlayerInput().getWire());

	//updating physics
	//Running the step simulation function to update rigidbodies in the physics environment
	//PhysFac->StepSimulation(1 / 60.f, 10, camera->GetCameraPosition());
	//the camera's position is updated in physics and based on collisions the new position is 
	//now set for the user.
	//camera->SetCameraPosition(camera->GetCameraPosition());
	//a temporary index is made for getting the UserIndex of a collision object in the physics environment
	//that index is used to make sure we update the correct position for an object.
	//currently this is only used to test for "asteroid_1"
	//int tempInd = gameWorld->getEnvironment()->getObject("asteroid_1")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	//gameWorld->getEnvironment()->getObject("asteroid_1")->updateObject(
		//PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	/*tempInd = gameWorld->getEnvironment()->getObject("asteroid_2")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("asteroid_2")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	tempInd = gameWorld->getEnvironment()->getObject("asteroid_3")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("asteroid_3")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	tempInd = gameWorld->getEnvironment()->getObject("asteroid_4")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("asteroid_4")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	tempInd = gameWorld->getEnvironment()->getObject("asteroid_5")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("asteroid_5")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	tempInd = gameWorld->getEnvironment()->getObject("asteroid_6")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("asteroid_6")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	tempInd = gameWorld->getEnvironment()->getObject("asteroid_7")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("asteroid_7")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	tempInd = gameWorld->getEnvironment()->getObject("asteroid_8")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("asteroid_8")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	tempInd = gameWorld->getEnvironment()->getObject("asteroid_9")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("asteroid_9")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));

	tempInd = gameWorld->getEnvironment()->getObject("Astroboy_1")->GetRigidBody()->getUserIndex();
	//This is to update the position of the object for drawing.
	gameWorld->getEnvironment()->getObject("Astroboy_1")->updateObject(
	PhysFac->GetXPosition(tempInd), PhysFac->GetYPosition(tempInd), PhysFac->GetZPosition(tempInd));
	*/
}
