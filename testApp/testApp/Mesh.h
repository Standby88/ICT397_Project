#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include "MathLib.h"

#include <assimp/Importer.hpp>

#include "Shader.h"

using namespace std;
class Skeleton;
class GameObject3D;
///holds all the information about a single vertex point
struct Vertex
{
	// Position
	V3 Position;
	// Normal
	V3 Normal;
	// TexCoords
	V2 TexCoords;
	//height of point
	float height;

	float weight[4];
	unsigned int id[4];
};

///holds the assimp information a texture
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
* @date 04/04/2018
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
	Skeleton* sceneLoaderSkeleton;
	
	/*  Functions  */
	// Constructor
	/**
	* @brief Mesh constructor that initializes a new mess given parameters
	*
	*@param vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture
	*/
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	
	void DrawCharacter(Shader shader, GameObject3D * parentGObj);
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