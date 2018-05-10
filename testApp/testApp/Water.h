#pragma once
#include "TextureManager.h"
#include "Shader.h"
#include "MathLib.h"
class Water
{
private:


	TextureManager m_TextureMan;
	GLuint VBO, VAO, EBO;
	GLuint t1;
	GLuint texture2;

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
public:

	Water(GLuint textureid)
	{
		std::cout << textureid << std::endl;
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

		t1 = textureid;
	}
	void drawWater(Shader S, M4 view, M4 projection)
	{
		S.Use();
		M4 model;

		glUniformMatrix4fv(glGetUniformLocation(S.Program, "projection"), 1, GL_FALSE, MathLib::value_ptr<const float *>(projection));
		glUniformMatrix4fv(glGetUniformLocation(S.Program, "view"), 1, GL_FALSE, MathLib::value_ptr<const float *>(view));
		model = MathLib::translate(model, V3(10.0f, 0.1f, 50));
		model = MathLib::scale(model, V3(50.0f, 50.0f, 50.0f));
		glUniformMatrix4fv(glGetUniformLocation(S.Program, "model"), 1, GL_FALSE, MathLib::value_ptr<const float *>(model));

		glUniform1i(glGetUniformLocation(S.Program, "t1"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t1);
		glUniform1i(t1, 0);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	~Water();
};

