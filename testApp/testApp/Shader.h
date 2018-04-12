#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//#include <GL\glew.h>
/**
* @class Shader
* @brief used to manage shaders that will be used for models
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
class Shader
{
public:

	//Shader(const GLchar *vertexPath, const GLchar *fragPath);

	/**
	* @brief Constructor used to initialize the shader 
	*
	*@param const char *vertexPath, const char *fragPath
	*/
	Shader(const char *vertexPath, const char *fragPath);

	/**
	* @brief Use shader
	*/
	void Use();

	/**
	* @brief destructor for shader object
	*/
	~Shader();

	///
	int Program;
	//GLuint Program;
};

