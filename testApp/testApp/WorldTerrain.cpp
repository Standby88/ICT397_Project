#include "WorldTerrain.h"

WorldTerrain::WorldTerrain()
{
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;
	objectModel = NULL;
}

void WorldTerrain::Draw()
{

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