#pragma once

#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>


#include "Camera.h"
#include "Model.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ScriptEngine.h"
#include "SceneRender.h"
#include "PlayerInput.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "GameAssetFactory.h"
#include "EnvironmentObjManager.h"


/*void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();*/
/**
* @class Graphics engine
* @brief USed to setup openGl and rednering
*
* @author alex
* @version 1
* @date
*
* @todo
*
* @bug
*/
class GraphicsEngine
{
public:
	/**
	* @brief Constructor for GraphicsEngine
	*/
	GraphicsEngine();

	/**
	* @brief desstructor for GraphicsEngine
	*/
	~GraphicsEngine();

	/**
	* @brief used to set up gl function and game loop
	*/
	bool GLFWpro();

	/// Window dimensions
	const GLint WIDTH = 800, HEIGHT = 600;
	int SCREEN_WIDTH, SCREEN_HEIGHT;

	///static texture
	ModelManager m_Models;
	TextureManager m_TextureMan;

	///scene camera and camera variables
	Camera  camera;
	GLdouble lastX = WIDTH / 2.0;
	GLdouble lastY = HEIGHT / 2.0;

	///input key states
	bool keys[1024];
	bool firstMouse = true;

	///wire drawing
	bool wire = false;

	///frame rate/game cycle variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	///photo variables
	GLuint VBO, VAO, EBO;
	GLuint texture1 = 0;
	GLuint texture2 = 0;
	
	/**
	* @brief used to set up photo for quiting
	*/
	void setupPhoto();

	/**
	* @brief draw exist photo
	*
	*@param shader
	*/
	void drawPhoto(Shader S);

	void setUpmanual()
	{
		GLfloat points[] =
		{
			// Positions          // Colors           // Texture Coords
			1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
			1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
			-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
			-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
		};

		GLuint indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// Texture Coordinate attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0); // Unbind VAO

		m_TextureMan = TextureManager::GetTextureManager();
		m_TextureMan.AddTexture("images/manual.png");

		texture2 = m_TextureMan.GetTexture("images/manual.png");
	}

	void drawMaunal(Shader S) 
	{
		S.Use();
		glUniform1i(glGetUniformLocation(S.Program, "texture2"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

};