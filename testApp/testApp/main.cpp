#include <iostream>
#include <iostream>
#include <string>
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>


#include "GraphicsEngine.h"

#include "GameAssetFactory.h"

#include "Enemy.h"
#include "Player.h"
#include "WorldTerrain.h"

#include "ScriptEngine.h"


using namespace luabridge;


int main()
{
	ScriptEngine * test = new ScriptEngine();
	//lua_State* L = luaL_newstate();
	//luaL_openlibs(L);

	GameAssetFactory<GameAsset, std::string>::scriptRegister(test->TempLuaState());
	BaseCreator<GameAsset>::scriptRegister(test->TempLuaState());

	
	getGlobalNamespace(test->TempLuaState())
		.beginNamespace("GAC")
		.deriveClass<GameAssetCreator<WorldTerrain, GameAsset>, BaseCreator<GameAsset>>("WorldTerrainCreator")
		.addConstructor<void(*) (void)>()
		.addFunction("Create", &GameAssetCreator<WorldTerrain, GameAsset>::Create)
		.endClass()
		.deriveClass<GameAssetCreator<Player, GameAsset>, BaseCreator<GameAsset>>("PlayerCreator")
		.addConstructor<void(*) (void)>()
		.addFunction("Create", &GameAssetCreator<Player, GameAsset>::Create)
		.endClass()
		.deriveClass<GameAssetCreator<Enemy, GameAsset>, BaseCreator<GameAsset>>("EnemyCreator")
		.addConstructor<void(*) (void)>()
		.addFunction("Create", &GameAssetCreator<Enemy, GameAsset>::Create)
		.endClass()
		.endNamespace();

	GameAsset::scriptRegister(test->TempLuaState());
	Enemy::scriptRegister(test->TempLuaState());
	Player::scriptRegister(test->TempLuaState());
	WorldTerrain::scriptRegister(test->TempLuaState());

	test->ExecuteFile("test.lua");


	GameAsset* enemy = getGlobal(test->TempLuaState(), "a");
	GameAsset* player = getGlobal(test->TempLuaState(), "b");
	GameAsset* worT = getGlobal(test->TempLuaState(), "c");
	std::cout << enemy->getID() << player->getID() << worT->getID()<<std::endl;
	system("pause");
	return 0;
}

/*getGlobalNamespace(L)
.beginNamespace("F")
.beginClass<Factory<Base, std::string>>("Factory")
.addConstructor<void(*) (void)>()
.addFunction("Register", &Factory<Base, std::string>::Register)
.addFunction("Create", &Factory<Base, std::string>::Create)
.addFunction("Print", &Factory<Base, std::string>::Print)
.endClass()
.endNamespace();

getGlobalNamespace(L)
.beginNamespace("B")
.beginClass<Base>("Base")
.addConstructor<void(*) (void)>()
.endClass()
.deriveClass<DerivedA, Base>("DerivedA")
.addConstructor<void(*) (void)>()
.addFunction("Get", &DerivedA::Get)
.endClass()
.deriveClass<DerivedB, Base>("DerivedB")
.addConstructor<void(*) (void)>()
.addFunction("Get", &DerivedB::Get)
.endClass()
.endNamespace();

getGlobalNamespace(L)
.beginNamespace("C")
.beginClass<Creator<Base>>("Creator")
.endClass()
.deriveClass<DerivedCreator<DerivedA, Base>, Creator<Base>>("DerivedCreatorA")
.addConstructor<void(*) (void)>()
.addFunction("Create", &DerivedCreator<DerivedA, Base>::Create)
.endClass()
.deriveClass<DerivedCreator<DerivedB, Base>, Creator<Base>>("DerivedCreatorB")
.addConstructor<void(*) (void)>()
.addFunction("Create", &DerivedCreator<DerivedB, Base>::Create)
.endClass()
.endNamespace();

*/