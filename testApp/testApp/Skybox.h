#pragma once

#include "GameObject.h"

#include "GL\glew.h"
#include "Shader.h"
#include "TextureManager.h"

#include <vector>

class Skybox : public GameObject
{
public:
	Skybox();

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

	void AddSkyboxPath(std::string path);

	bool ClearSkyboxPath();

	void GenSkybox();

	void Draw(Shader &S);


	~Skybox();

private:
	std::vector<std::string> faces;

	GLuint skyboxVAO, skyboxVBO;

	GLuint skyboxTex;

	//skybox vertices (in ANY instance) won't change so that can be defined staticly
	//GLfloat * skyboxVertices;
};

