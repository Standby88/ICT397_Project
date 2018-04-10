#pragma once

#include "GameObject3D.h"
#include "Model.h"
class EnvironmentObject : public GameObject3D
{
private:
	
public:

	EnvironmentObject();
	~EnvironmentObject();
	void Draw(Shader S);

	static void scriptRegister(lua_State * L);

};
