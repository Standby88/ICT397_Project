#include "GameWorld.h"

GameWorld::GameWorld(/*CharacterManager * cha,*/ TerrainManager * ter, EnvironmentObjManager * en)
{
	//this->characters = cha;
	this->terrain = ter;
	this->environment = en;
}

CharacterManager * GameWorld::getCharacters()
{
	return characters;
}

TerrainManager * GameWorld::getTerrain()
{
	return terrain;
}

EnvironmentObjManager * GameWorld::getEnvironment()
{
	return environment;
}

void GameWorld::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GW")
		.beginClass<GameWorld>("GameWorld")
		.addConstructor<void(*) (TerrainManager*, EnvironmentObjManager*)>()
		.endClass()
		.endNamespace();
}

GameWorld::~GameWorld()
{
}
