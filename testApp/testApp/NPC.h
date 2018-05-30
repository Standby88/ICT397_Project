#pragma once
#include "GameObject3D.h"

/**
* @class NPC
* @brief NPCs inherit from GameObject3D class and encapsulate data specific to NPCs
*
* @author 
* @version 1
* @date
*
* @todo
*
* @bug
*/
class NPC : public GameObject3D
{
public:

	///Default constructor
	NPC();

	///Default destructor
	~NPC();

	/**
	* @brief Draws an NPC
	* @param Shader&
	* @return void
	*/
	void Draw(Shader &S);

	/**
	* @brief expose functions to lua
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

	/**
	* @brief converts a GameObject to an NPC
	* @param GameObject*
	* @return NPC*
	*/
	NPC * convert(GameObject * a);
};

