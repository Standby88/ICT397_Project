#pragma once
#include "GameWorld.h"
#include "Camera.h"
#include "PlayerInput.h"
#include <iostream>
#include "Serialization.h"
#include "GameAssetFactory.h"
#include "ModelManager.h"

struct saveVec
{
	float x, y, z;

	template<class Archive>
	void serialize(Archive & save)
	{
		save(x,y,z);
	}
};

struct enObj
{
	saveVec Pos;
	saveVec RotAxis;
	float angle;
	std::string modelName;

	template<class Archive>
	void serialize(Archive & save)
	{
		save(Pos, RotAxis, angle, modelName);
	}
};

/**
* @class GameController
* @brief
*
* @author Des
* @version 1
* @date
*
* @author Kieron
* @version 2
* @date 26/04/2018, Added a PhysicsFacade instance object to access Physics methods.
*
* @author Kieron van der Kwast
* @version 3
* @date 28/05/2018, added a check that will loop though update once, then sets menu
*				to be displayed, essentially starting the game in the menu.
*
* @todo
*
* @bug
*/
class GameController
{
private:
	///int variable 
	int startCount;
	///Camera* variable
	Camera*  camera;
	///GameWorld* variable
	GameWorld* gameWorld;
	///PlayerInput* variable
	PlayerInput playerInput;
	///PhysicsFacade* variable
	PhysicsFacade* PhysFac;
	///std::unordered_map with std::string keys and EnvironmentObject* values
	std::unordered_map<std::string, EnvironmentObject* > environmentObjList;
	///std::unordered_map<>::iterator with std::string keys and EnvironmentObject* values
	std::unordered_map<std::string, EnvironmentObject* >::iterator envItr;
	///std::unordered_map with std::string keys and NPC* values
	std::unordered_map<std::string, NPC* > nPCList;
	///std::unordered_map<>::iterator with std::string keys and NPC* values
	std::unordered_map<std::string, NPC* >::iterator nPCItr;
	///std::vector of NPC* variables
	std::vector<NPC*> updateCharList;

public:

	///Default constructor
	GameController(GameWorld* gw);

	///Default Destructor
	~GameController();

	/**
	* @brief updates the game
	* @param GLfloat
	* @return void
	*/
	void update(GLfloat deltaTime);

	/**
	* @brief returns the Camera* used for the game
	* @param void
	* @return Camera*
	*/
	Camera* getGameCamera();

	/**
	* @brief serialises game data
	* @param void
	* @return void
	*/
	void saveGame();
	
	/**
	* @brief deserialises game data
	* @param void
	* @return void
	*/
	void loadGame();
	
};

