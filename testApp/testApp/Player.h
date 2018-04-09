#pragma once
#include "GameAsset.h"
class Player : public GameAsset
{
private:
	std::string id;
public:
	Player()
	{
		id = "Player";
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
			.deriveClass<Player, GameAsset>("Player")
			.addConstructor<void(*) (void)>()
			.addFunction("getID", &Player::getID)
			.endClass()
			.endNamespace();
	}
};