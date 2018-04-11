#include "TerrainManager.h"



TerrainManager::TerrainManager()
{
}


TerrainManager::~TerrainManager()
{
}

void TerrainManager::RemoveTerrain(int i)
{
	terrainList[i] = NULL;
	delete terrainList[i];
	terrainList.shrink_to_fit();
}
