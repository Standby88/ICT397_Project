#include <Vector>
#include "WorldTerrain.h"


/**
* @class TerrainManager
* @brief used to manage the terrains in the scene
*
*
* @author Desmond
* @version 1
* @date
*
* @todo
*
* @bug
*/
class TerrainManager
{
private:

	///List used to store the terrains
	std::vector<WorldTerrain*> TerrainList;
	
public:

	/**
	* @brief Constructor for the terrain Manager
	*/
	TerrainManager();

	/**
	* @brief destructor for manager. Correctly releases memory used for pointer
	*
	*/
	~TerrainManager();

	/**
	* @brief used to add terrain into the list
	*
	*@param GameObject* in
	*/
	void AddTerrain(GameObject* in);

	/**
	* @brief used to render terrain
	*
	*/
	void DrawTerrain(Shader S);

	/**
	* @brief remove terrain pointer from list given index
	*
	*@param int i
	*/
	void RemoveTerrain(int i);

	/**
	* @brief returns a terrain pointer given an index
	*
	*@param int i
	*@return WorldTerrain*
	*/
	WorldTerrain* getTerrain(int i);

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

	/**
	* @brief used to return the whole terrain list
	*
	* @return std::vector<WorldTerrain*>&
	*/
	std::vector<WorldTerrain*>& getTerrainList();


};