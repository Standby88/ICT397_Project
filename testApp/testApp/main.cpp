#include <iostream>
#include "ScriptEngine.h"
int main()
{
	
	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->getLuaState());
	LuaEn->doLuaScript("Game.lua");
	EnvironmentObjManager * Etest = NULL;
	CharacterManager * Ctest = NULL;
	Etest = getGlobal(LuaEn->getLuaState(), "EnObjMan");
	Etest->DrawAllObjects();
	Ctest = getGlobal(LuaEn->getLuaState(), "ChMan");
	Ctest->drawPlayer();
	getchar();
	return 0;
}

