#include "GameController.h"

GameController::GameController(GameWorld * gw)
{
	PhysFac = PhysicsFacade::GetPhysicsInstance();
	gameWorld = gw;
	camera = Camera::GetCameraInstance();
	startCount = 0;	//should be initialised to 0
	gameWorld->setProjection(MathLib::perspective(camera->GetZoom(), (float)gameWorld->getScreenW() / (float)gameWorld->getScreenH(), 0.1f, 10000.0f));
	playerInput = PlayerInput::getCurrentPlayerInput();
	playerInput.SetAttributes(camera);
	playerInput.SetCallbacks();

	environmentObjList = gameWorld->getEnvironment()->getEnObjMap();

	//for loop that uses an iterator to go through and add object's rigidbodies to the physics world
	for (envItr = environmentObjList.begin(); envItr != environmentObjList.end(); envItr++)
	{
		std::cout << "size environment : " << environmentObjList.size() << std::endl;
		if ((*envItr).second->GetRigidBody())
		{
			PhysFac->AddRigidBody((*envItr).second->GetRigidBody());
		}
		else
		{
			cout << "No rigid body for " << (*envItr).first << std::endl;
		}
	}

	nPCList = gameWorld->getCharacters()->getCharMap();

	
	for (nPCItr = nPCList.begin(); nPCItr != nPCList.end(); nPCItr++)
	{
		if ((*nPCItr).second->GetRigidBody())
		{
			//cout << "UserId = " << (*nPCItr).second->GetRigidBody()->getUserIndex() << std::endl;
			PhysFac->AddRigidBody((*nPCItr).second->GetRigidBody());
			//cout << "UserId = " << (*nPCItr).second->GetRigidBody()->getUserIndex() << std::endl;
		}
		else
		{
			cout << "No rigid body for " << (*nPCItr).first << std::endl;
		}
	}
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
	camera = Camera::GetCameraInstance();
	gameWorld->setView(camera->GetViewMatrix());
	gameWorld->setPhoto(PlayerInput::getCurrentPlayerInput().getPhoto());
	gameWorld->setManual(PlayerInput::getCurrentPlayerInput().getManual());
	gameWorld->setWorldDisplay(PlayerInput::getCurrentPlayerInput().getWorldDisplay());
	gameWorld->setWire(PlayerInput::getCurrentPlayerInput().getWire());
	gameWorld->setMainMenu(PlayerInput::getCurrentPlayerInput().getMainMenu());
	gameWorld->SetSaveGame(PlayerInput::getCurrentPlayerInput().GetSaveGame());
	gameWorld->SetLoadGame(PlayerInput::getCurrentPlayerInput().GetLoadGame());
	gameWorld->SetNewGame(PlayerInput::getCurrentPlayerInput().GetNewGame());

	if (startCount == 1)
	{
		PlayerInput::getCurrentPlayerInput().SetWorldDisplay(false);
		PlayerInput::getCurrentPlayerInput().SetMenuDisplay(true);
		gameWorld->setWorldDisplay(PlayerInput::getCurrentPlayerInput().getWorldDisplay());
		gameWorld->setMainMenu(PlayerInput::getCurrentPlayerInput().getMainMenu());
	}

	//need help
	//std::cout << "x: " << camera->GetCameraPosition().x << "y: " << camera->GetCameraPosition().y <<"z: "<< camera->GetCameraPosition().z << std::endl;
	if (gameWorld->getWorldDisplay() == true)
	{
		
		//updating physics
		//Running the step simulation function to update rigidbodies in the physics environment
		PhysFac->StepSimulation(1 / 30.f, 10, camera->GetCameraPosition());

		//the camera's position is updated in physics and based on collisions the new position is 
		//now set for the user.
		camera->SetCameraPosition(camera->GetCameraPosition());
		environmentObjList = gameWorld->getEnvironment()->getEnObjMap();
		//initialise an int to store userIndex so that the value doesn't need to be constantly retrieved
		//also takes up less space and looks a little neater.
		int tempInd = 0;
		//for loop the uses an iterator to go through and update the positions of all environment objects and their rigidbodies
		for (envItr = environmentObjList.begin(); envItr != environmentObjList.end(); envItr++)
		{

				//a temporary index is made for getting the UserIndex of a collision object in the physics environment
				//that index is used to make sure we update the correct position for an object.
				tempInd = (*envItr).second->GetRigidBody()->getUserIndex();
				//std::cout << "UserIndex for object: " << tempInd << std::endl;
				//This is to update the position of the object for drawing.
				if ((*envItr).second->getStatic() == false)
				{
					(*envItr).second->updateObject(PhysFac->GetXPosition(tempInd),
					PhysFac->GetYPosition(tempInd),
					PhysFac->GetZPosition(tempInd));
				}
				
		}
		
		updateCharList = gameWorld->getCharacters()->getUpdateList();
		tempInd = 0;
		for (int i = 0; i<updateCharList.size(); i++)
		{

				tempInd = updateCharList[i]->GetRigidBody()->getUserIndex();
				updateCharList[i]->updateObject(PhysFac->GetXPosition(tempInd),
					PhysFac->GetYPosition(tempInd),
					PhysFac->GetZPosition(tempInd));
		}
	}
	
	if (gameWorld->GetSaveGame())
	{
		std::cout << "Game is being saved..." << std::endl;
		saveGame();
		//make sure to reset the variable in playerinput so saving doesn't occur
		//multiple times
		PlayerInput::getCurrentPlayerInput().SetSaveGame(false);
	}

	if (gameWorld->GetLoadGame())
	{
		std::cout << "Game is being loaded..." << std::endl;
		loadGame();
		//make sure to reset the variable in playerinput so loading doesn't occur
		//multiple times
		PlayerInput::getCurrentPlayerInput().SetLoadGame(false);
	}

	if (gameWorld->GetNewGame())
	{
		std::cout << "Beginning new game..." << std::endl;
		//not implemented yet
		//make sure to reset the variable in playerinput so starting a new game
		//doesn't occur multiple times
		PlayerInput::getCurrentPlayerInput().SetNewGame(false);
	}

	//this allows code to run through once before switching from world being displayed
	//to menu being displayed.
	if (startCount == 0)
	{
		startCount = 1;
	}
	else
	{
		startCount = 2;
	}
	

}

Camera * GameController::getGameCamera()
{
	return Camera::GetCameraInstance();
}

void GameController::saveGame()
{
	std::vector<enObj> enList;
	std::unordered_map<std::string, EnvironmentObject* > temp = gameWorld->getEnvironment()->getEnObjMap();
	std::unordered_map<std::string, EnvironmentObject* >::iterator itr;
	for (itr = temp.begin(); itr != temp.end(); ++itr)
	{
		enObj holder;
		holder.angle = (*itr).second->getObjectAngle();
		holder.Pos.x = (*itr).second->getObjectPos().x;
		holder.Pos.y = (*itr).second->getObjectPos().y;
		holder.Pos.z = (*itr).second->getObjectPos().z;
		holder.RotAxis.x = (*itr).second->getObjectRotation().x;
		holder.RotAxis.y = (*itr).second->getObjectRotation().y;
		holder.RotAxis.z = (*itr).second->getObjectRotation().z;
		holder.modelName = (*itr).second->getModel()->getName();
		std::cout << holder.modelName << std::endl;
		enList.push_back(holder);
	}
	Serialization::saveData(enList, "SaveGame.xml");
}

void GameController::loadGame()
{
	std::vector<enObj> enList = Serialization::loadData<std::vector<enObj>>("SaveGame.xml");
	EnvironmentObjManager * enManager = new EnvironmentObjManager();
	GameAssetFactory<GameObject, std::string > factory;
	factory.Register("enObjCreator", new GameAssetCreator<EnvironmentObject, GameObject>);
	for (int i = 0; i < enList.size(); i++)
	{
		EnvironmentObject *temp = dynamic_cast<EnvironmentObject*>(factory.Create("enObjCreator"));
		temp->updateObject(enList[i].Pos.x, enList[i].Pos.y, enList[i].Pos.z);
		temp->updateObjectRotation(enList[i].angle, enList[i].RotAxis.x, enList[i].RotAxis.y, enList[i].RotAxis.z);
		temp->addModel(gameWorld->getModels()->GetModel(enList[i].modelName));
		enManager->addObject(temp, to_string(i));
	}
	gameWorld->setEnvironment(enManager);
	enManager = nullptr;
	delete enManager;
}