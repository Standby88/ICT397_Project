#include "Player.h"

Player::Player()
{
	objectType = "PlayerType";
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;
	objectModel = NULL;
}

Player::~Player()
{
	objectModel = NULL;
	delete objectModel;
}

void Player::Draw(Shader &S)
{
	objectModel->Draw(S);
}

void Player::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<Player, GameObject>("Player")
		.addConstructor<void(*) (void)>()
		.addFunction("Draw", &Player::Draw)
		.endClass()
		.endNamespace();
}