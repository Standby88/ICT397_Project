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
class GameObject3D;
typedef unsigned int uint;
#define NUM_BONES_PER_VEREX 4
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
};

///holds the assimp information a texture
struct Texture
{
	GLuint id;
	string type;
	aiString path;
};
struct BoneMatrix
{
	aiMatrix4x4 offset_matrix;
	aiMatrix4x4 final_world_transform;

};
struct VertexBoneData
{
	uint ids[NUM_BONES_PER_VEREX];   // we have 4 bone ids for EACH vertex & 4 weights for EACH vertex
	float weights[NUM_BONES_PER_VEREX];

	VertexBoneData()
	{
		memset(ids, 0, sizeof(ids));    // init all values in array = 0
		memset(weights, 0, sizeof(weights));
	}

	void addBoneData(uint bone_id, float weight)
	{
		for (uint i = 0; i < NUM_BONES_PER_VEREX; i++)
		{
			if (weights[i] == 0.0)
			{
				ids[i] = bone_id;
				weights[i] = weight;
				return;
			}
		}
	}
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
	
	vector<VertexBoneData> bones_id_weights_for_each_vertex;

	/*  Functions  */
	// Constructor
	/**
	* @brief Mesh constructor that initializes a new mess given parameters
	*
	*@param vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> texture
	*/
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, vector<VertexBoneData> bone_id_weights);
	
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
	void setTerrainMesh();

private:
	/*  Render data  */
	
	GLuint VAO;
	GLuint VBO_vertices;
	GLuint VBO_bones;
	GLuint EBO_indices; 
	
	GLuint VAOT, VBOT, EBOT;


	/**
	* @brief Initializes all the buffer objects/arrays
	*/
	void setupMesh();
	
};