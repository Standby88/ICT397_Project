#pragma once

#include "GameObject.h"

#include "GL\glew.h"

#include "TextureManager.h"

#include <vector>

class Skybox
{
public:
	Skybox();

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

	void AddSkyboxPath(const GLchar * path);

	bool ClearSkyboxPath();

	void GenSkybox();

	void Draw();


	~Skybox();

private:
	std::vector<const GLchar *> faces;

	GLuint skyboxVAO, skyboxVBO;

	GLuint skyboxTex;

	//skybox vertices (in ANY instance) won't change so that can be defined staticly
	//GLfloat * skyboxVertices;
};

