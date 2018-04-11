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
	void AddTerrain(WorldTerrain* Wt)
	{
		terrainList.push_back(Wt);
	}
	void DrawTerrain()
	{
		for (int i = 0; i < terrainList.size(); i++)
		{
			(*terrainList[i]).Draw();
		}
		
	}
	void RemoveTerrain(int i);
	WorldTerrain* getTerrain(int i)
	{
		return terrainList[i];
	}

};