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

	Camera*  camera;

	GameWorld* gameWorld;

	PlayerInput playerInput;

	PhysicsFacade* PhysFac;

public:

	GameController(GameWorld* gw);

	~GameController();

	void update(GLfloat deltaTime);
	
	void saveGame()
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
	void loadGame()
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
};

