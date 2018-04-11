#include "ScriptEngine.h"


ScriptEngine::~ScriptEngine()
{
	lua_close(MainLuaState); 
}

lua_State* ScriptEngine::tempLuaState()
{
	return MainLuaState;
}


void ScriptEngine::report_errors(int a)
{
	if (a != 0)
	{
		std::cerr << "ErrorMessage: " << lua_tostring(MainLuaState, a) << std::endl;
		lua_pop(MainLuaState, 1); 
	}
}

//executes a lua script file
void ScriptEngine::doLuaScript(const char* file)
{
	if (file == NULL)
		return;

	int state = luaL_dofile(MainLuaState, file);
	report_errors(state);
}