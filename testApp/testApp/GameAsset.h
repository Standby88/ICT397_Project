#pragma once

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
#include <string>
class GameAsset
{
public:
	virtual ~GameAsset() {};

	virtual std::string getID() = 0;

	static void scriptRegister(lua_State * L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("GA")
			.beginClass<GameAsset>("GameAsset")
			.endClass()
			.endNamespace();
	}
};