#pragma once
#include "EnvironmentObjManager.h"
#include "TerrainManager.h"
#include "CharacterManager.h"
class GameWorld
{
private:
	CharacterManager * characters;
	TerrainManager * terrain;
	EnvironmentObjManager * environment;
public:
	GameWorld(/*CharacterManager * cha,*/ TerrainManager * ter, EnvironmentObjManager * en);
	CharacterManager* getCharacters();
	TerrainManager* getTerrain();
	EnvironmentObjManager* getEnvironment();
	static void scriptRegister(lua_State * L);
	~GameWorld();
};

