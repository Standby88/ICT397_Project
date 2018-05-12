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
	GameWorld* gameWorld;
	std::map<std::string, Shader*> shaders;
	Menu * menu;
	Water * water;
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

	void renderMenu(Shader& s);

	void renderCharacters(CharacterManager & TM, M4 view, M4 projection, Shader& s);
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

	void renderGameScene()
	{
		EnvironmentObjManager *Eom = gameWorld->getEnvironment();
		TerrainManager *Tm = gameWorld->getTerrain();
		CharacterManager *Cm = gameWorld->getCharacters();
		renderCharacters(*Cm, gameWorld->getView(), gameWorld->getProjection(), *shaders["environment"]);
		renderEnvironmentObj(*Eom, gameWorld->getView(), gameWorld->getProjection(), *shaders["environment"]);
		renderTerrain(*Tm, gameWorld->getView(), gameWorld->getProjection(), *shaders["terrain"]);
	}
	
	void renderWater()
	{
		fbos.bindReflectionFrameBuffer(); 
		float distance = 2 * (gameWorld->getCam()->GetCameraPosition().y - 0);
		gameWorld->getCam()->GetCameraPosition().y -= distance;
		gameWorld->getCam()->flipPitch();
		renderGameScene();
		gameWorld->getCam()->GetCameraPosition().y += distance;
		gameWorld->getCam()->flipPitch();
		fbos.unbindCurrentFrameBuffer();

		fbos.bindRefractionFrameBuffer();
		renderGameScene();
		fbos.unbindCurrentFrameBuffer();

		water->drawWater(*shaders["water"], gameWorld->getView(), gameWorld->getProjection());

	}
	 static void scriptRegister(lua_State * L);

};

