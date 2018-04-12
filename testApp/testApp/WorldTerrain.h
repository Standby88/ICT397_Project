#pragma once
#include "GameObject.h"

/**
* @class WorldTerrain
* @brief used to represent terrain of the world
*
*
* @author 
* @version 1
* @date
*
* @todo
*
* @bug
*/
class WorldTerrain : public GameObject
{
private:

	///temp test string
	std::string th;
public:

	/**
	* @brief World terrain constructor
	*
	*/
	WorldTerrain();
	
	/**
	* @brief destructor for worldterrain object
	*/
	~WorldTerrain();

	/**
	* @brief render the terrain
	*/
	void Draw();

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);
	
};

