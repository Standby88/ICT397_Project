#include <iostream>
#include "ScriptEngine.h"
#include "GraphicsEngine.h"
int main()
{
	GraphicsEngine t;
	t.GLFWpro();
	/*
	ScriptEngine * LuaEn = new ScriptEngine();
	ScriptEngine::expFuncToLua(LuaEn->getLuaState());
	LuaEn->doLuaScript("Game.lua");
	EnvironmentObjManager * Etest = NULL;
	CharacterManager * Ctest = NULL;
	Etest = getGlobal(LuaEn->getLuaState(), "EnObjMan");
	Etest->DrawAllObjects();
	Ctest = getGlobal(LuaEn->getLuaState(), "ChMan");
	Ctest->drawPlayer();*/
	getchar();
	return 0;
}

