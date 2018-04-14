#pragma once
#include "GameObject.h"
#include <vector>
#include "RAwIMGLoader.h"
#include "Mesh.h"
struct VertexRGB
{
	float t[6];
};
/**
* @class WorldTerrain
* @brief used to represent terrain of the world
*
*
* @author 
* @version 1
* @date
*
* @todo
*
* @bug
*/
class WorldTerrain : public GameObject
{
private:

	Mesh terMesh;
	///temp test string
	unsigned char *terrainData;
	glm::vec3 scale;
	std::vector<Vertex> vertecies;
	vector<GLuint> indices;
	std::vector<unsigned char> hcolor;
	int size;

	bool inbounds(int xpos, int zpos);
	unsigned char getHeightColor(int xpos, int zpos);
	float getHeight(int xpos, int zpos);
public:

	/**
	* @brief World terrain constructor
	*
	*/
	WorldTerrain();
	
	/**
	* @brief destructor for worldterrain object
	*/
	~WorldTerrain();

	/**
	* @brief render the terrain
	*/
	void Draw(Shader);

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);
	
	void collectData();

	bool loadHeightfield(char *filename, const int size);

	void setScalingFactor(glm::vec3 newScale);


	int getSize();
};

