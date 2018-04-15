#pragma once
#include "GameObject3D.h"
/**
* @class PlayerObject
* @brief class used to create players
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
class Player : public GameObject3D
{
private:
	
public:
	/**
	* @brief Constructor for initializing player position and type values
	*/
	Player();

	/**
	* @brief destructor for player. properly releases model pointer memory
	*/
	~Player();

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

};