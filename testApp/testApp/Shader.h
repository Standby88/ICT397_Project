#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
#include <string>
#include <glm\glm.hpp>

/**
* @class Shader
* @brief used to compile and setup shader programs
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

	/**
	* @brief Constructor used to initialize the shader
	*
	*@param const char *vertexPath, const char *fragPath
	*/
	Shader(const char *vertexPath, const char *fragPath);

	/**
	* @brief Use shader program
	*/
	void Use();

	/**
	* @brief destructor for shader object
	*/
	~Shader();


	/**
	* @brief used to register the functions to ua
	*
	*@param lua_state * L
	*/
	static void scriptRegister(lua_State * L);
	

	int Program;
};

