#pragma once

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "GL\glew.h"


#include "SOIL2\SOIL2.h"

/**
* @class TextureManager
* @brief used to manage textures and load new textures
*
*
* @author alex
* @version 1
* @date
*
* @todo
*
* @bug
*/
class TextureManager
{
public:

	/**
	* @brief Constructor used to initialize the textureManager
	*
	*/
	TextureManager();

	/**
	* @brief destructor for texturemanager
	*/
	~TextureManager();

	/**
	* @brief add texture to the map
	*
	*@param const std::string path
	*@return bool
	*/
	bool AddTexture(const std::string path);

	/**
	* @brief return a texture using the path as key
	*
	*@param const std::string path
	*@return GLuint
	*/
	GLuint GetTexture(const std::string path);
	
	/**
	* @brief return a textureManager instance
	*
	*@return TextureManager& 
	*/
	static TextureManager & GetTextureManager();

	/**
	* @brief used to destroy texture manager
	*
	*/
	void DestroyTextureManager();

	static GLuint LoadSkyboxCubeMap(std::vector<std::string> faces);

	GLuint GetSkyboxCubeMap();

private:

	/**
	* @brief helper function used to load texture from a filepath
	*
	*/
	GLuint LoadTexture(const std::string path);

	///map used to store the textures mapped to a string
	std::map <std::string, GLuint> textures;

	GLuint skybox;
};

