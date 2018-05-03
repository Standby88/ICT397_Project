#pragma once
#include "EnvironmentObjManager.h"
#include "TerrainManager.h"
#include "CharacterManager.h"
#include "ModelManager.h"
class GameWorld
{
private:
	CharacterManager * characters;
	TerrainManager * terrain;
	EnvironmentObjManager * environment;
	ModelManager * models;
	bool photo;
	bool manual;
	bool worldDisplay;
	bool wire;
	M4 view;
	M4 projection;

	int SCREEN_WIDTH, SCREEN_HEIGHT;
public:
	GameWorld(/*CharacterManager * cha,*/ TerrainManager * ter, EnvironmentObjManager * en);
	CharacterManager* getCharacters();
	TerrainManager* getTerrain();
	EnvironmentObjManager* getEnvironment();
	void setEnvironment(EnvironmentObjManager * en)
	{
		environment = nullptr;
		environment = en;
	}
	void setModels(ModelManager * models)
	{
		this->models = models;
	}
	ModelManager * getModels()
	{
		return this->models;
	}
	static void scriptRegister(lua_State * L);
	~GameWorld();
	void setManual(bool man);
	void setPhoto(bool pho);
	void setWorldDisplay(bool wor);
	void setWire(bool wir);

	bool getWire();
	bool getManual();
	bool getPhoto();
	bool getWorldDisplay();
	void setScreenHW(int w, int h);

	int getScreenH();

	int getScreenW();

	void setView(M4 v);


	void setProjection(M4 p);


	M4 getView();


	M4 getProjection();

};

