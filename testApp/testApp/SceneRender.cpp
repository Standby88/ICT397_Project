#include "SceneRender.h"
#include <glm\gtc\type_ptr.hpp>

SceneRender::SceneRender()
{
}


SceneRender::~SceneRender()
{
}

void SceneRender::renderEnvironmentObj(EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S)
{
	std::unordered_map<std::string, EnvironmentObject* > drawMap = EM.getEnObjMap();
	glm::vec3 posVec;
	S.Use();
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(S.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	
	std::unordered_map<std::string, EnvironmentObject* >::iterator itr;
	int i = 0;
	for (itr = drawMap.begin(); itr != drawMap.end(); ++itr)
	{
		glm::mat4 model;
		posVec = (*itr).second->getObjectPos();
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
