#include <Vector>
#include "WorldTerrain.h"
class TerrainManager
{
private:

	typedef std::vector<WorldTerrain*> TerrainList;
	TerrainList terrainList;
public:
	TerrainManager();
	~TerrainManager();
	void AddTerrain(GameObject* in);
	void DrawTerrain();
	void RemoveTerrain(int i);
	WorldTerrain* getTerrain(int i);
	static void scriptRegister(lua_State * L);


};