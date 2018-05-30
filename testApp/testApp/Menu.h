#pragma once
#include "TextureManager.h"
#include "Shader.h"
#include "MathLib.h"

/**
* @class Menu
* @brief used to encapsulate Menu information and functions
*
* @author 
* @version 1
* @date
*
* @todo
*
* @bug
*/
class Menu
{
private:

	///TextureManager variable
	TextureManager m_TextureMan;
	///GLuint varaibles for buffer and array objects
	GLuint VBO, VAO, EBO;
	///GLuint varaible for a texture
	GLuint texture1;
	///GLuint varaible for a texture
	GLuint texture2;
	///GLuint varaible for a texture
	GLuint texture3;
	///GLfloat array for points
	GLfloat points[32] =
	{
		// Positions          // Colors           // Texture Coords
		1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
	};
	///GLuint array for indices
	GLuint indices[6] =
	{
		0, 1, 3,
		1, 2, 3
	};

	/**
	* @brief sets up a photo for display in the menu
	* @param void
	* @return void
	*/
	void setupPhoto();

	/**
	* @brief sets up a main menu for display in the menu
	* @param void 
	* @return void 
	*/
	void setUpMainMenu();
	
	/**
	* @brief sets up a manual for display in the menu
	* @param void 
	* @return void
	*/
	void setUpmanual();

public:

	///Default constructor
	Menu();
	
	///Default destructor
	~Menu();
	
	/**
	* @brief draws a photo
	* @param Shader
	* @return void
	*/
	void drawPhoto(Shader S);
	
	/**
	* @brief draws a manual
	* @param Shader
	* @return void
	*/
	void drawMaunal(Shader S);

	/**
	* @brief draws a main menu
	* @param Shader
	* @return void
	*/
	void drawMainMenu(Shader s);
};

