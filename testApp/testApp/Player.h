#pragma once
#include "GameObject3D.h"
class Player : public GameObject3D
{
private:
	
public:
	Player();
	~Player();
	void Draw(Shader &S);
	static void scriptRegister(lua_State * L);

};