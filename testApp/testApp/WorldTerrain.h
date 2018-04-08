#pragma once
#include "Terrain.h"
class WorldTerrain : public Terrain
{
private:
	int id;
public:
	WorldTerrain()
	{
		id = 1;
	}
	int getID()
	{
		return id;
	}
};

