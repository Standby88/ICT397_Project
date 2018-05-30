#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>

/**
* @class Window
* @brief used to represent window of a game
*
* @author 
* @version 1
* @date
*
* @todo 
*
* @bug
*/
class Window
{
private:
	///GLFWwindow pointer variable
	GLFWwindow *window;
	///constant integers for width and height of game window
	const GLint WIDTH = 800, HEIGHT = 600;
	///integers for screen width and screen height
	int SCREEN_WIDTH, SCREEN_HEIGHT;

public:

	/**
	* @brief returns SCREEN_HEIGHT
	*@param void
	*@return int
	*/
	int getScreenHeight()
	{
		return SCREEN_HEIGHT;
	}

	/**
	* @brief returns SCREEN_WIDTH
	*@param void
	*@return int
	*/
	int getScreenWidth()
	{
		return SCREEN_WIDTH;
	}

	/**
	* @brief checks the close flag for window
	*@param void
	*@return int
	*/
	int windowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	/**
	* @brief swaps buffers during display
	*@param void
	*@return void
	*/
	void swapBuffers()
	{
		glfwSwapBuffers(window);
	}

	/**
	* @brief sets window clear colour
	*@param void
	*@return void
	*/
	void clearBufferNColor()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	///Default constructor
	Window();

	///Default destructor
	~Window();
};

