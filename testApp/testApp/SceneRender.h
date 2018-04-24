#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Shader.h"
#include "GameWorld.h"
#include "Menu.h"
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

	void renderScene(glm::mat4 view, glm::mat4 projection);
	/**
	* @brief used to render environment objects
	*@param EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S
	*/
	void renderEnvironmentObj(EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S);

	/**
	* @brief used to render terrain
	*@param EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S
	*/
	 void renderTerrain(TerrainManager & TM, glm::mat4 view, glm::mat4 projection, Shader &S);

	 void renderMenu(Shader& s);

	 static void scriptRegister(lua_State * L);

};

