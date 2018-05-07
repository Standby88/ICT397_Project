#pragma once
#include <iostream>
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
#include <string>
#include "MathLib.h"

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
	V3 objectPos;
	V3 rotateAxis;
	float angle;

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
	* @brief used to update the rotation of the object
	*
	*@param float w, float x, float y, float z
	*/
	void updateObjectRotation(float w, float x, float y, float z);

	/**
	* @brief used to access objects position
	*
	*@pretun vec3
	*/
	V3 getObjectPos();

	/**
	* @brief used to access objects rotation
	*
	*@pretun vec3
	*/
	V3 getObjectRotation();

	/**
	* @brief used to access objects angle of rotation
	*
	*@pretun float
	*/
	float getObjectAngle();

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);
	
};