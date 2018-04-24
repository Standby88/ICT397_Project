#include "SceneRender.h"
#include <glm\gtc\type_ptr.hpp>


SceneRender::SceneRender(GameWorld * gw)
{
	gameWorld = gw;
	menu = new Menu();
}

void SceneRender::addShader(std::string ver, std::string frag, std::string name)
{
	Shader * s = new Shader(ver, frag);
	typedef std::pair<std::string, Shader*> temp;
	shaders.insert(temp(name, s));
}

SceneRender::~SceneRender()
{
	gameWorld = nullptr;
	delete gameWorld;

	menu = nullptr;
	delete menu;

	std::map<std::string, Shader*>::iterator itr;
	for (itr = shaders.begin(); itr != shaders.end(); ++itr)
	{
		itr->second = nullptr;
		delete itr->second;
	}

}

void SceneRender::renderScene()
{
	if (gameWorld->getWire() == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


	if (gameWorld->getWorldDisplay() == false)
	{
		renderMenu(*shaders["menuOption"]);
	}
	else 
	{
		EnvironmentObjManager *Eom = gameWorld->getEnvironment();
		TerrainManager *Tm = gameWorld->getTerrain();
		renderEnvironmentObj(*Eom, gameWorld->getView(), gameWorld->getProjection(), *shaders["environment"]);
		renderTerrain(*Tm, gameWorld->getView(), gameWorld->getProjection(), *shaders["terrain"]);
	}
	
}

void SceneRender::renderEnvironmentObj(EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S)
{
	std::unordered_map<std::string, EnvironmentObject* > drawMap = EM.getEnObjMap();
	glm::vec3 posVec;
	glm::vec3 rotateAxis;
	float angle;
	S.Use();
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	
	std::unordered_map<std::string, EnvironmentObject* >::iterator itr;
	int i = 0;
	for (itr = drawMap.begin(); itr != drawMap.end(); ++itr)
	{
		glm::mat4 model;
		posVec = (*itr).second->getObjectPos();
		angle = (*itr).second->getObjectAngle();
		rotateAxis = (*itr).second->getObjectRotation();
		if (angle > 0.0f)
			model = glm::rotate(model, angle, rotateAxis);
		model = glm::translate(model, posVec); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(S.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		(*itr).second->Draw(S);
	}
}

void SceneRender::renderTerrain(TerrainManager & TM, glm::mat4 view, glm::mat4 projection, Shader & S)
{
	std::vector<WorldTerrain*> Tlist = TM.getTerrainList();
	glm::vec3 posVec;
	S.Use();
	glm::mat4 model;
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	std::vector<WorldTerrain*>::iterator itr;
	for (itr = Tlist.begin(); itr != Tlist.end(); ++itr)
	{
		posVec = (*itr)->getObjectPos();
		// Draw the loaded model
		model = glm::translate(model, posVec); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(S.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		(*itr)->Draw(S);
	}
}

void SceneRender::renderMenu(Shader& s)
{
	if (gameWorld->getManual() == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		menu->drawMaunal(s);
	}
	else 
	if (gameWorld->getPhoto() == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		menu->drawPhoto(s);
	}
	
}

void SceneRender::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("SR")
		.beginClass<SceneRender>("SceneRender")
		.addConstructor<void(*) (GameWorld*)>()
		.addFunction("addShader", &SceneRender::addShader)
		.endClass()
		.endNamespace();
}
