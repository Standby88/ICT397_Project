#pragma once
#include "EnvironmentObjManager.h"
#include "TerrainManager.h"
#include "CharacterManager.h"
#include "ModelManager.h"
#include "Camera.h"
#include "Skybox.h"
class GameWorld
{
private:
	CharacterManager * characters;
	TerrainManager * terrain;
	EnvironmentObjManager * environment;
	ModelManager * models;
	Camera * camera;
	Skybox * skybox;
	bool photo;
	bool manual;
	bool worldDisplay;
	bool mainMenu;
	bool wire;
	M4 view;
	M4 projection;

	int SCREEN_WIDTH, SCREEN_HEIGHT;
public:
	GameWorld(CharacterManager * cha, TerrainManager * ter, EnvironmentObjManager * en, Skybox *in);
	CharacterManager* getCharacters();
	TerrainManager* getTerrain();
	EnvironmentObjManager* getEnvironment();
	Skybox * getSkybox();
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
	void setMainmenu(bool menu);

	bool getWire();
	bool getMainMenu();
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

	Camera* getCam()
	{
		return camera;
	}
};

