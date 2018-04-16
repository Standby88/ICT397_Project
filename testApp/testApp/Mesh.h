#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>

#include "Shader.h"

using namespace std;

struct Vertex
{
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;
	//height of point
	float height;
};

struct Texture
{
	GLuint id;
	string type;
	aiString path;
};
/**
* @class Mesh
* @brief Used to store mesh details and handle mesh use
*
* @author Alex
* @version 1
* @date
*
* @todo
*
* @bug
*/
class Mesh
{
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	GLuint terrainTex[4];

	
	/*  Functions  */
	// Constructor
	/**
	* @brief Mesh constructor that initializes a new mess given parameters
	*
	*@param vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture
	*/
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	

	/**
	* @brief Mesh default constructor constructor 
	*
	*
	*/
	Mesh();


	/**
	* @brief sets mesh details after construction
	*
	*
	*/
	void setMesh();


	/**
	* @brief Draw function used to render terrain mesh
	*
	*@param Shader shader
	*/
	void drawTerrain(Shader shader);
	

	/**
	* @brief Draw function used to render mesh in scene
	*
	*@param Shader shader
	*/
	void Draw(Shader shader);
	

private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;

	/**
	* @brief Initializes all the buffer objects/arrays
	*/
	void setupMesh();
	
};