#include "TerrainManager.h"



TerrainManager::TerrainManager()
{
}


TerrainManager::~TerrainManager()
{
	TerrainList::iterator itr;
	for (itr = terrainList.begin(); itr != terrainList.end(); ++itr)
	{
		delete (*itr);
	} 
}

void TerrainManager::AddTerrain(GameObject * in)
{
	WorldTerrain*Wt = dynamic_cast<WorldTerrain*>(in);
	terrainList.push_back(Wt);
}
void TerrainManager::DrawTerrain()
{
	for (int i = 0; i < terrainList.size(); i++)
	{
		(*terrainList[i]).Draw();
	}

}
void TerrainManager::RemoveTerrain(int i)
{
	terrainList[i] = NULL;
	delete terrainList[i];
	terrainList.shrink_to_fit();
}

WorldTerrain * TerrainManager::getTerrain(int i)
{
	return terrainList[i];
}

void TerrainManager::scriptRegister(lua_State * L)
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