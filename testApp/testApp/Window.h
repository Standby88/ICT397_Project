#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>
class Window
{
private:
	GLFWwindow *window;
	const GLint WIDTH = 800, HEIGHT = 600;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
public:
	int getScreenHeight()
	{
		return SCREEN_HEIGHT;
	}
	int getScreenWidth()
	{
		return SCREEN_WIDTH;
	}
	int windowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}
	void swapBuffers()
	{
		glfwSwapBuffers(window);
	}
	void clearBufferNColor()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	Window();
	~Window();
};

