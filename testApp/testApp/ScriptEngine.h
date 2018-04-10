#pragma once
#include <iostream>

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class ScriptEngine
{
public:

	ScriptEngine(void) : MainLuaState(luaL_newstate()) 
	{ 
		luaL_openlibs(MainLuaState); 
	}

	ScriptEngine(const ScriptEngine& other); 

	ScriptEngine& operator=(const ScriptEngine&);

	~ScriptEngine(void) { lua_close(MainLuaState); } 


	lua_State* TempLuaState();

	void ExecuteFile(const char* file);

	void ExecuteString(const char* expression);

private:

	lua_State* MainLuaState;

private:
	void report_errors(int state);
};