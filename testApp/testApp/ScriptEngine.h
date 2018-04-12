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

/**
* @class ScriptEngine
* @brief used to manage lua scripts
*
*
* @author Desmond Ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
using namespace luabridge;
class ScriptEngine
{
private:

	///stores the lua state
	lua_State* MainLuaState;

	/**
	* @brief used to report errors to console for debugging lua script
	*/
	void errorReport(int state);

public:

	/**
	* @brief Constructor for lua state. Creates new lua state to be used by scripts
	*/
	ScriptEngine() : MainLuaState(luaL_newstate()) 
	{ 
		luaL_openlibs(MainLuaState); 
	}

	/**
	* @brief destructor for ScriptEngine that ends the lua state
	*/
	~ScriptEngine();

	/**
	* @brief used to run a lua script from a lua script file
	*
	*@param const char* file
	*/
	void doLuaScript(const char* file);

	/**
	* @brief used to expose all object functions to lua to be used
	*
	*@param lua_State * L
	*/
	static void expFuncToLua(lua_State * L);

	/**
	* @brief accessor for local lua state
	*
	*@return lua_State*
	*/
	lua_State* getLuaState();

};