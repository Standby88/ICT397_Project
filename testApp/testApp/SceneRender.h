#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "GameWorld.h"
#include "Menu.h"
#include "MathLib.h"
#include <map>
#include "Water.h"
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
	Water *test;
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
	void addWater(Water * w)
	{
		test = w;
	}
	void renderWater()
	{
		test->drawWater(*shaders["water"], gameWorld->getView(), gameWorld->getProjection());

	}
	 static void scriptRegister(lua_State * L);

};

