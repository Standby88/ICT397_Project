#include "TerrainManager.h"

TerrainManager::TerrainManager()
{
}

TerrainManager::~TerrainManager()
{
	std::vector<WorldTerrain*>::iterator itr;
	for (itr = TerrainList.begin(); itr != TerrainList.end(); ++itr)
	{
		delete (*itr);
	} 
}

void TerrainManager::AddTerrain(GameObject * in)
{
	WorldTerrain*Wt = dynamic_cast<WorldTerrain*>(in);
	TerrainList.push_back(Wt);
}
void TerrainManager::DrawTerrain(Shader S)
{
	for (int i = 0; i <  TerrainList.size(); i++)
	{
		(*TerrainList[i]).Draw(S);
	}
}
void TerrainManager::RemoveTerrain(int i)
{
	TerrainList[i] = NULL;
	delete  TerrainList[i];
	TerrainList.shrink_to_fit();
}

WorldTerrain * TerrainManager::getTerrain(int i)
{
	return  TerrainList[i];
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

std::vector<WorldTerrain*>& TerrainManager::getTerrainList()
{
	return TerrainList;
}