#pragma once

#include <map>
#include <iostream>
#include <string>
#include "GL\glew.h"
#include <vector>

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

	static GLuint LoadCubemap(std::vector<const GLchar * > faces)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);

		int imageWidth, imageHeight;
		unsigned char *image;

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		for (GLuint i = 0; i < faces.size(); i++)
		{
			image = SOIL_load_image(faces[i], &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return textureID;
	}
private:

	/**
	* @brief helper function used to load texture from a filepath
	*
	*/
	GLuint LoadTexture(const std::string path);

	///map used to store the textures mapped to a string
	std::map <std::string, GLuint> textures;
};

