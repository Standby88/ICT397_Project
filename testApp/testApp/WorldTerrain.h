#pragma once
#include "GameAsset.h"
class WorldTerrain : public GameAsset
{
private:
	std::string id;
public:
	WorldTerrain()
	{
		id = "WorldTerrain";
	}
	std::string getID()
	{
		return id;
	}
	static void scriptRegister(lua_State * L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("GA")
			.deriveClass<WorldTerrain, GameAsset>("WorldTerrain")
			.addConstructor<void(*) (void)>()
			.addFunction("getID", &WorldTerrain::getID)
			.endClass()
			.endNamespace();
	}
};

