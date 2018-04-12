#pragma once

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
* @class GameObject
* @brief Abstract class that all other game objects inherit from
*
* @author Desmond Ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
class GameObject
{
protected:

	///Stores where the object is located in the scene
	glm::vec3 objectPos;

public:

	/**
	* @brief Constructor for GameObject initializes position to 0
	*/
	GameObject();
	
	/**
	* @brief Virtual destructor
	*/
	virtual ~GameObject() {};

	/**
	* @brief used to update the position of the object
	*
	*@param float x, float y, float z
	*/
	void updateObject(float x, float y, float z);

	/**
	* @brief used to access objects position
	*
	*@pretun vec3
	*/
	glm::vec3 getObjectPos();

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);
	
};