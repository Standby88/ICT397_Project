#pragma once

#include "GameObject.h"
#include "GL\glew.h"
#include "TextureManager.h"
#include <vector>

/**
* @class Skybox
* @brief used to handle the creation and drawing of a skybox
*
* @author alex
* @version 1
* @date
*
* @todo
*
* @bug
*/
class Skybox
{
public:

	///Default constructor
	Skybox();

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

	/**
	* @brief adds a file path
	*
	*@param const GLchar *path
	*@return void
	*/
	void AddSkyboxPath(const GLchar * path);

	/**
	* @brief clears a file path
	*
	*@param void
	*@return bool
	*/
	bool ClearSkyboxPath();

	/**
	* @brief Generates a skybox
	*
	*@param void
	*@return void
	*/
	void GenSkybox();

	/**
	* @brief Draws skybox
	*
	*@param void
	*@return void
	*/
	void Draw();

	///Default destructor
	~Skybox();

private:
	///std::vector of const GLchar* for faces
	std::vector<const GLchar *> faces;
	///GLuint variables for array and buffer objects
	GLuint skyboxVAO, skyboxVBO;
	///GLuint variable for skybox texture
	GLuint skyboxTex;

	//skybox vertices (in ANY instance) won't change so that can be defined staticly
	//GLfloat * skyboxVertices;
};

