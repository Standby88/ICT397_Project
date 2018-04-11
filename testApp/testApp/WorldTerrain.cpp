#include "WorldTerrain.h"
#include <iostream>
WorldTerrain::WorldTerrain()
{
	th = "Terrain";
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;
}

WorldTerrain::~WorldTerrain()
{

}

void WorldTerrain::Draw()
{
	std::cout << th << std::endl;
}
void WorldTerrain::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<WorldTerrain, GameObject>("WorldTerrain")
		.addConstructor<void(*) (void)>()
		.addFunction("Draw", &WorldTerrain::Draw)
		.endClass()
		.endNamespace();
}