#pragma once

#include "GameObject3D.h"
#include "Model.h"

/**
* @class EnvironmentObject
* @brief class used to create objects like trees and buildings
*
*
* @author Desmond Ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
class EnvironmentObject : public GameObject3D
{
private:
	///boolean flag for if an object is static
	bool isStatic;
public:

	/**
	* @brief returns isStatic boolean flag
	* @param void
	* @return bool
	*/
	bool getStatic()
	{
		return isStatic;
	}

	/**
	* @brief sets isStatic boolean flag
	* @param bool
	* @return void
	*/
	void setStatic(bool t)
	{
		isStatic = t;
	}

	/**
	* @brief Constructor for environment objsct. sets positons to 0,0,0 and sets the objectType to EnvironmentObject
	*/
	EnvironmentObject();

	/**
	* @brief destructor for environment object. properly releases model pointer memory
	*/
	~EnvironmentObject();

	/**
	* @brief Used to draw the object by calling its model draw and passing in the correct shader
	*
	*@param Shader &S
	*/
	void Draw(Shader &S);

	/**
	* @brief used to register the functions to ua
	*
	*@param lua_state * L
	*/
	static void scriptRegister(lua_State * L);

	/**
	* @brief used to register the functions to ua
	*
	*@param GameObject* a
	*@return EnvironmentObject*
	*/
	EnvironmentObject* convert(GameObject* a);

};
