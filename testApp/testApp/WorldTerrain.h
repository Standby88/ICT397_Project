#pragma once
#include "GameObject.h"
#include "RAwIMGLoader.h"
#include "Mesh.h"
#include "TextureManager.h"
class WorldTerrain : public GameObject
{
private:

	Mesh terMesh;
	///temp test string
	unsigned char *terrainData;
	glm::vec3 scale;

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