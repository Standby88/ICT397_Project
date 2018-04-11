#pragma once
#include <iostream>
#include "TerrainManager.h"
#include "CharacterManager.h"
#include "EnvironmentObjManager.h"
#include "GameAssetFactory.h"
#include "GameAssetCreator.h"
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
using namespace luabridge;
class ScriptEngine
{
private:
	lua_State* MainLuaState;
	void report_errors(int state);

public:

	ScriptEngine() : MainLuaState(luaL_newstate()) 
	{ 
		luaL_openlibs(MainLuaState); 
	}
	~ScriptEngine();
	void doLuaScript(const char* file);
	static void expFuncToLua(lua_State * L);
	lua_State* getLuaState();

};