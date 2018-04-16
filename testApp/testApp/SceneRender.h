#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Shader.h"
#include "EnvironmentObjManager.h"
#include "TerrainManager.h"

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
public:

	/**
	* @brief Constructor for SceneRender
	*/
	SceneRender();

	/**
	* @brief desstructor for SceneRender
	*/
	~SceneRender();

	/**
	* @brief used to render environment objects
	*@param EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S
	*/
	static void renderEnvironmentObj(EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S);

	/**
	* @brief used to render terrain
	*@param EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S
	*/
	static void renderTerrain(TerrainManager & TM, glm::mat4 view, glm::mat4 projection, Shader &S);
};

