#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Shader.h"
#include "EnvironmentObjManager.h"
#include "TerrainManager.h"


class SceneRender
{
public:
	SceneRender();
	~SceneRender();
	static void renderEnvironmentObj(EnvironmentObjManager& EM, glm::mat4 view, glm::mat4 projection, Shader &S);
	static void renderTerrain(TerrainManager & TM, glm::mat4 view, glm::mat4 projection, Shader &S);
};

