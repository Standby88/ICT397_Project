#pragma once

#include "GameAsset.h"
class Enemy : public GameAsset
{
private:
	std::string id;
public:
	Enemy()
	{
		id = "Enemy";
	}
	std::string getID()
	{
		return id;
	}
	static void scriptRegister(lua_State * L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("GA")
			.deriveClass<Enemy, GameAsset>("Enemy")
			.addConstructor<void(*) (void)>()
			.addFunction("getID", &Enemy::getID)
			.endClass()
			.endNamespace();
	}
};
