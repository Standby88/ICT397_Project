#pragma once
#include "GameObject3D.h"
class NPC : public GameObject3D
{
public:
	NPC();
	~NPC();
	void Draw(Shader &S);
	static void scriptRegister(lua_State * L);
	NPC * convert(GameObject * a);
};

