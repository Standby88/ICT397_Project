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
	lua_State* tempLuaState();
	void doLuaScript(const char* file);
	static void expFuncToLua(lua_State * L)
	{
		GameAssetFactory<GameObject, std::string>::scriptRegister(L);
		BaseCreator<GameObject>::scriptRegister(L);
		getGlobalNamespace(L)
			.beginNamespace("GAC")
			.deriveClass<GameAssetCreator<WorldTerrain, GameObject>, BaseCreator<GameObject>>("WTCreator")
			.addConstructor<void(*) (void)>()
			.addFunction("Create", &GameAssetCreator<WorldTerrain, GameObject>::Create)
			.endClass()
			.deriveClass<GameAssetCreator<EnvironmentObject, GameObject>, BaseCreator<GameObject>>("EOCreator")
			.addConstructor<void(*) (void)>()
			.addFunction("Create", &GameAssetCreator<EnvironmentObject, GameObject>::Create)
			.endClass()
			.deriveClass<GameAssetCreator<Player, GameObject>, BaseCreator<GameObject>>("PCreator")
			.addConstructor<void(*) (void)>()
			.addFunction("Create", &GameAssetCreator<Player, GameObject>::Create)
			.endClass()
			.endNamespace();
		
		TerrainManager::scriptRegister(L);
		EnvironmentObjManager::scriptRegister(L);
		CharacterManager::scriptRegister(L);

		GameObject::scriptRegister(L);
		GameObject3D::scriptRegister(L);
		Player::scriptRegister(L);
		WorldTerrain::scriptRegister(L);
		EnvironmentObject::scriptRegister(L);

	}
};