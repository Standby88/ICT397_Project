#include <iostream>
#include "ScriptEngine.h"
int main()
{
	
	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->tempLuaState());
	LuaEn->doLuaScript("Game.lua");
	EnvironmentObjManager * Etest = NULL;
	CharacterManager * Ctest = NULL;
	Etest = getGlobal(LuaEn->tempLuaState(), "EnObjMan");
	Etest->DrawAllObjects();
	Ctest = getGlobal(LuaEn->tempLuaState(), "ChMan");
	Ctest->drawPlayer();
	getchar();
	return 0;
}

