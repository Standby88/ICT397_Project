#pragma once
#include "TextureManager.h"
#include "Shader.h"
class Menu
{
private:

	TextureManager m_TextureMan;
	GLuint VBO, VAO, EBO;
	GLuint texture1;
	GLuint texture2;
	GLuint texture3;

	GLfloat points[32] =
	{
		// Positions          // Colors           // Texture Coords
		1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
	};

	GLuint indices[6] =
	{
		0, 1, 3,
		1, 2, 3
	};

	void setupPhoto();
	//void setupPhoto(const char* filePath);
	void setUpmanual();
	void setUpMainMenu();
public:
	Menu();
	~Menu();
	void drawPhoto(Shader S);
	void drawMaunal(Shader S);
	void drawMainMenu(Shader S);
};

