#pragma once
#include "GameObject.h"
#include "RawIMGLoader.h"
#include "Mesh.h"
#include "TextureManager.h"
#include "SOIL2/SOIL2.h"
#include "PhysicsFacade.h"

/**
* @class WorldTerrain
* @brief used to represent terrain of the world
*
*
* @author Desmond
* @version 1
* @date
*
* @author Kieron van der Kwast
* @version 2
* @date 1/05/2018, added a rigidbody variable so the terrain is collidable
*
* @todo properly map terrain to collision shape
*
* @bug
*/
class WorldTerrain : public GameObject
{
private:

	///store terrain mesh data
	Mesh terMesh;
	unsigned char *terrainData;
	V3 scale;
	int size;
	
	///access PhysicsFacade
	PhysicsFacade* wPhysFac = PhysicsFacade::GetPhysicsInstance();

	///facaded rigidbody variable
	rigidBody* terrainBody;

	/**
	* @brief helper function used to check if x and z pos is in heightmap
	*@param int xpos, int zpos
	*@return bool
	*/
	bool inbounds(int xpos, int zpos);

	/**
	* @brief helper function used get height color value
	*@param int xpos, int zpos
	*@return unsigned char
	*/
	unsigned char getHeightColor(int xpos, int zpos);

	/**
	* @brief helper function used get height at point
	*@param int xpos, int zpos
	*@return float
	*/
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

	/**
	* @brief used to set terrain mesh, indicies and texture
	*@param std::string, std::string, std::string, std::string
	*/
	void SetTerrainVariable(std::string, std::string, std::string, std::string);

	/**
	* @brief load a terrain from height field
	*@param std::string , const int size
	*/
	bool loadHeightfield(std::string , const int size);

	/**
	* @brief set the scalling factor of the terrain to make it smaller or bigger
	*@param float x, float y, float z
	*/
	void setScalingFactor(float x, float y, float z);

	/**
	* @brief convert a GameObjectBase to Worldterrain
	*@param GameObject* a
	*@return WorldTerrain*
	*/
	WorldTerrain* convert(GameObject* a)
	{
		return dynamic_cast<WorldTerrain*>(a);
	}

	int getSize();

	void CreateTerrainRigidBody();
};