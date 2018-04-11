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
	void AddTerrain(GameObject* in)
	{
		WorldTerrain*Wt = dynamic_cast<WorldTerrain*>(in);
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
	static void scriptRegister(lua_State * L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("TM")
			.beginClass<TerrainManager>("TerrainManager")
			.addConstructor<void(*) (void)>()
			.addFunction("AddTerrain", &TerrainManager::AddTerrain)
			.addFunction("DrawTerrain", &TerrainManager::DrawTerrain)
			.addFunction("RemoveTerrain", &TerrainManager::RemoveTerrain)
			.addFunction("getTerrain", &TerrainManager::getTerrain)
			.endClass()
			.endNamespace();
	}

};