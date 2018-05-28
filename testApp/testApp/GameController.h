#pragma once
#include "GameWorld.h"
#include "Camera.h"
#include "PlayerInput.h"
#include <iostream>
#include "Serialization.h"
#include "GameAssetFactory.h"
#include "ModelManager.h"
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
* @author Kieron van der Kwast
* @version 3
* @date 28/05/2018, added a check that will loop though update once, then sets menu 
				to be displayed, essentially starting the game in the menu.
*
* @todo
*
* @bug
*/
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
class GameController
{
private:

	int startCount;

	Camera*  camera;

	GameWorld* gameWorld;

	PlayerInput playerInput;

	PhysicsFacade* PhysFac;

	std::unordered_map<std::string, EnvironmentObject* > environmentObjList;
	std::unordered_map<std::string, EnvironmentObject* >::iterator envItr;

	std::unordered_map<std::string, NPC* > nPCList;
	std::unordered_map<std::string, NPC* >::iterator nPCItr;

	std::vector<NPC*> updateCharList;

public:

	GameController(GameWorld* gw);

	~GameController();

	void update(GLfloat deltaTime);

	Camera* getGameCamera();
	
	void saveGame();
	
	void loadGame();
	
};

