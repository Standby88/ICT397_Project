#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "GameWorld.h"
#include "Menu.h"
#include "MathLib.h"

#include <map>
#include "Water.h"
#include "WaterFrameBuffer.h"

/**
* @class SceneRender
* @brief USed to render scene onjects
*
* @author Desmond
* @version 1
* @date
*
* @todo
*
* @bug
*/
class SceneRender
{
private:
	//ModelManager m_Models;
	///GameWorld pointer varaible
	GameWorld* gameWorld;
	///Std::map with std::strings as keys and Shader* as values
	std::map<std::string, Shader*> shaders;
	///Menu pointer variable
	Menu * menu;
	///Water pointer varaible
	Water * water;
	///WaterFrameBuffer variable
	WaterFrameBuffer fbos;

	/**
	* @brief used to render environment objects
	*@param EnvironmentObjManager& EM, M4 view, M4 projection, Shader &S
	*/
	void renderEnvironmentObj(EnvironmentObjManager& EM, M4 view, M4 projection, Shader &S);

	/**
	* @brief used to render terrain
	*@param EnvironmentObjManager& EM, M4 view, M4 projection, Shader &S
	*/
	void renderTerrain(TerrainManager & TM, M4 view, M4 projection, Shader &S);

	/**
	* @brief used to render the skybox
	*@param skybox& sky, M4 view, M4 projection, Shader &S
	*/
	void renderSkybox(Skybox & sky, M4 view, M4 projection, Shader &S);

	/**
	* @brief used to render the menu
	*@param Shader&
	*/
	void renderMenu(Shader& s);

	/**
	* @brief used to render characters
	*@param CharacterManager&, M4, M4, Shader&, Shader&
	*/
	void renderCharacters(CharacterManager & TM, M4 view, M4 projection, Shader & animation, Shader & deflt);


public:

	/**
	* @brief Constructor for SceneRender
	* @param GameWorld*
	*/
	SceneRender(GameWorld* gw);

	/**
	* @brief adds shaders
	*@param std::string, std::string, std::string
	*/
	void addShader(std::string ver, std::string frag, std::string name);

	///Default destructor for SceneRender
	~SceneRender();

	/**
	* @brief renders the scene
	* @param void
	* @return void
	*/
	void renderScene();

	/**
	* @brief renders game scene
	* @param void
	* @return void
	*/
	void renderGameScene();
	
	/**
	* @brief renders water
	* @param void
	* @return void
	*/
	void renderWater();
	
	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

	/**
	* @brief returns a shader
	* @param std::string
	* @return Shader*
	*/
	Shader* getShader(std::string name);
};

