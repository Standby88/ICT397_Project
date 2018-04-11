#pragma once
#include "GameObject.h"
class WorldTerrain : public GameObject
{
private:
	std::string th;
public:
	WorldTerrain();
	
	~WorldTerrain();

	void Draw();

	static void scriptRegister(lua_State * L);
	
};

