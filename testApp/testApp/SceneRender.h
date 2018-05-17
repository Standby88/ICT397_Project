#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "GameWorld.h"
#include "Menu.h"
#include "MathLib.h"

#include "Camera.h"

#include <map>
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
	GameWorld* gameWorld;
	std::map<std::string, Shader*> shaders;
	Menu * menu;

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
	void renderSkybox(Skybox & sky, M4 projection, Shader &S);

	void renderMenu(Shader& s);

public:

	/**
	* @brief Constructor for SceneRender
	*/
	SceneRender(GameWorld* gw);

	void addShader(std::string ver, std::string frag, std::string name);
	/**
	* @brief desstructor for SceneRender
	*/
	~SceneRender();

	void renderScene();


	 static void scriptRegister(lua_State * L);

};

