#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>


#include "Camera.h"
/**
* @class PlayerInput
* @brief manages player input
*
* @author alex
* @version 1
* @date
*
* @author Kieron van der Kwast
* @version 2
* @date 28/05/2018, Implemented functions for getting and setting various boolean values
				and also implemented menu functionalities.
* @todo
*
* @bug
*/
class PlayerInput
{
public:
	/**
	* @brief Constructor for Playerinput
	*/
	PlayerInput();

	/**
	* @brief desstructor for playerinput
	*/
	~PlayerInput();

	/**
	* @brief Constructor for Playerinput that initialises values
	*/
	PlayerInput(int width, int height, Camera *cam, GLfloat *deltaTime);

	/**
	* @brief return player input instance
	*@return playerinput&
	*
	*/
	static PlayerInput & getCurrentPlayerInput();

	/**
	* @brief helper function that releases memory of playerinput
	*/
	static void destroyCurrentPlayerInput();

	/**
	* @brief does the player movement
	*
	*@param GLfloat 
	*/
	void DoMovement(GLfloat time);

	/**
	* @brief set input atributes
	* 
	*@param Camera*
	*/
	void SetAttributes(Camera * cam);

	/**
	* @brief set callback functions
	*
	*/
	void SetCallbacks();

	/**
	* @brief used to wrap key call back function
	*
	*@param GLFWwindow *window, int key, int scancode, int action, int mode
	*/
	static void WrapKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

	/**
	* @brief used to wrap mouse call back function
	*
	*@param GLFWwindow *window, double xPos, double yPos
	*/
	static void WrapMouseCallback(GLFWwindow *window, double xPos, double yPos);

	/**
	* @brief used to wrap mouse scroll call back function
	*
	*@param GLFWwindow *window, double xOffset, double yOffset
	*/
	static void WrapScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

	/**
	* @brief returns true if photo is to be displayed
	*
	* @return bool
	*/
	bool getPhoto();
	
	/**
	* @brief returns true if manual is to be displayed
	*
	* @return bool
	*/
	bool getManual();

	/**
	* @brief returns true if gameworld is to be displayed
	*
	* @return bool
	*/
	bool getWorldDisplay();

	/**
	* @brief sets if gameworld is to be displayed
	*
	* @param bool
	* @return void
	*/
	void SetWorldDisplay(bool dispWorld);

	/**
	* @brief returns true if wireframe is to be displayed
	*
	* @return bool
	*/
	bool getWire();

	/**
	* @brief returns true if main menu is to be displayed
	*
	* @return bool
	*/
	bool getMainMenu();

	/**
	* @brief sets if menu is to be displayed
	* 
	* @param bool
	* @return void
	*/
	void SetMenuDisplay(bool dispMenu);

	/**
	* @brief returns true if save game has been selected
	*
	* @return bool
	*/
	bool GetSaveGame();

	/**
	* @brief sets save game to true or false
	*
	* @param bool
	* @return void
	*/
	void SetSaveGame(bool hasSaved);

	/**
	* @brief returns true if load game has been selected
	*
	* @return bool
	*/
	bool GetLoadGame();

	/**
	* @brief sets load game to true or false
	*
	* @param bool
	* @return void
	*/
	void SetLoadGame(bool load);

	/**
	* @brief returns true if new game has been selected
	*
	* @return bool
	*/
	bool GetNewGame();

	/**
	* @brief sets new game to true or false
	*
	* @param bool
	* @return void
	*/
	void SetNewGame(bool load);

private:
	
	GLfloat m_time;
	///local camera points to existing camera
	Camera *camera;
	///width and height of screen
	int w, h;

	///stores mouse movement
	GLfloat lastX;
	GLfloat lastY;

	///keyboord states
	bool keys[1024];

	///mouse movement
	bool firstMouse;

	/**
	* @brief used to do keyboard functions
	*
	*@param GLFWwindow *window, int key, int scancode, int action, int mode
	*/
	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

	/**
	* @brief used to move camera according to mouse movement
	*
	*@param GLFWwindow *window, double xPos, double yPos
	*/
	void MouseCallback(GLFWwindow *window, double xPos, double yPos);

	/**
	* @brief used to change camera zoom
	*
	*@param GLFWwindow *window, double xOffset, double yOffset
	*/
	void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

	///end photo display variable
	bool photo;

	///draw wireframe
	bool wire ;
	///draw manual
	bool manual;
	///world display variable
	bool worldDisplay;
	///main menu display variable
	bool mainMenu;
	///save game variable
	bool saveGame;
	///load game variable
	bool loadGame;
	///new game variable
	bool newGame;
};

