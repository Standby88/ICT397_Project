#pragma once
#include "EnvironmentObjManager.h"
#include "TerrainManager.h"
#include "CharacterManager.h"
#include "ModelManager.h"
#include "Camera.h"
#include "Skybox.h"

/**
* @class Gameworld
* @brief Used to manage the game world
*
*
* @author Desmond ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
class GameWorld
{
private:
	///CharavterManager* variable
	CharacterManager * characters;
	///TerrainManager* variable
	TerrainManager * terrain;
	///EnvironmentObjManager* variable
	EnvironmentObjManager * environment;
	///ModelManager* variable
	ModelManager * models;
	///Camera* varaible
	Camera * camera;
	///Skybox* variable
	Skybox * skybox;
	///bool flag for photo to be displayed
	bool photo;
	///bool flag for manual to be displayed
	bool manual;
	///bool flag for world to be displayed
	bool worldDisplay;
	///bool flag for main menu to be displayed
	bool mainMenu;
	///bool flag for wireframe to be displayed
	bool wire;
	///bool flag for game to be saved
	bool saveGame;
	///bool flag for game to be loaded
	bool loadGame;
	///bool flag for new game to be started
	bool newGame;

	///M4 variable for view matrix
	M4 view;
	///M4 variable for projection matrix
	M4 projection;
	///int variables for screen width and screen height
	int SCREEN_WIDTH, SCREEN_HEIGHT;

public:

	/**
	* @brief Constructor for GameWorld
	* @param CharacterManager*, TerrainManager*, EnvironmentObjManager*, Skybox*
	*/
	GameWorld(CharacterManager * cha, TerrainManager * ter, EnvironmentObjManager * en, Skybox *in);

	/**
	* @brief gets Characters for game world
	* @param void
	* @return CharacterManager*
	*/
	CharacterManager* getCharacters();

	/**
	* @brief Gets terrain for game world
	* @param void
	* @return TerrainManager*
	*/
	TerrainManager* getTerrain();

	/**
	* @brief Gets environment objects for game world
	* @param void
	* @return EnvironmentObjManager
	*/
	EnvironmentObjManager* getEnvironment();

	/**
	* @brief gets skybox for game world
	* @param void
	* @return Skybox*
	*/
	Skybox * getSkybox();

	/**
	* @brief sets environment objects in game world
	* @param EnvironmentObjManager*
	* @return void
	*/
	void setEnvironment(EnvironmentObjManager * en)
	{
		environment = nullptr;
		environment = en;
	}

	/**
	* @brief Sets models in game world
	* @param ModelManager*
	* @return void
	*/
	void setModels(ModelManager * models)
	{
		this->models = models;
	}

	/**
	* @brief returns models in game world
	* @param void 
	* @return ModelManager*
	*/
	ModelManager * getModels()
	{
		return this->models;
	}

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

	///Default destructor
	~GameWorld();

	/**
	* @brief sets manual boolean flag
	* @param bool
	* @return void
	*/
	void setManual(bool man);

	/**
	* @brief sets photo boolean flag
	* @param bool
	* @return void
	*/
	void setPhoto(bool pho);

	/**
	* @brief sets world display boolean flag
	* @param bool
	* @return void
	*/
	void setWorldDisplay(bool wor);

	/**
	* @brief sets wireframe display boolean flag
	* @param
	* @return
	*/
	void setWire(bool wir);

	/**
	* @brief sets main menu boolean flag
	* @param bool
	* @return void
	*/
	void setMainMenu(bool menu);

	/**
	* @brief sets save game boolean flag
	* @param bool
	* @return void
	*/
	void SetSaveGame(bool hasSaved);

	/**
	* @brief sets load game boolean flag 
	* @param bool
	* @return void
	*/
	void SetLoadGame(bool load);

	/**
	* @brief sets new game boolean flag 
	* @param bool
	* @return void
	*/
	void SetNewGame(bool newG);

	/**
	* @brief returns wireframe display boolean flag
	* @param void
	* @return bool
	*/
	bool getWire();

	/**
	* @brief returns main menu display boolean flag
	* @param void
	* @return bool
	*/
	bool getMainMenu();

	/**
	* @brief returns manual display boolean flag
	* @param void
	* @return bool
	*/
	bool getManual();

	/**
	* @brief returns photo display boolean flag
	* @param void
	* @return bool
	*/
	bool getPhoto();

	/**
	* @brief returns world display boolean flag
	* @param void
	* @return bool
	*/
	bool getWorldDisplay();

	/**
	* @brief returns save game boolean flag
	* @param void
	* @return bool
	*/
	bool GetSaveGame();

	/**
	* @brief returns load game boolean flag
	* @param void
	* @return bool
	*/
	bool GetLoadGame();

	/**
	* @brief returnsnew game boolean flag
	* @param void
	* @return bool
	*/
	bool GetNewGame();

	/**
	* @brief sets screen height and width
	* @param int, int
	* @return void
	*/
	void setScreenHW(int w, int h);

	/**
	* @brief returns screen height
	* @param void
	* @return int
	*/
	int getScreenH();

	/**
	* @brief returns screen width
	* @param void
	* @return int
	*/
	int getScreenW();

	/**
	* @brief sets view matrix
	* @param M4
	* @return void
	*/
	void setView(M4 v);

	/**
	* @brief sets projection matrix
	* @param M4
	* @return void
	*/
	void setProjection(M4 p);

	/**
	* @brief returns view matrix
	* @param void
	* @return M4
	*/
	M4 getView();

	/**
	* @brief returns projection matrix
	* @param void 
	* @return M4
	*/
	M4 getProjection();

	/**
	* @brief returns camera pointer variable
	* @param void
	* @return Camera*
	*/
	Camera* getCam()
	{
		return camera;
	}
};
