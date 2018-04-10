#pragma once

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
#include <string>
#include <glm\glm.hpp>

class GameObject
{
protected:
	glm::vec3 objectPos;

public:

	GameObject();
	
	virtual ~GameObject() {};

	void updateObject(float x, float y, float z);

	glm::vec3 getObjectPos();

	//virtual void Draw() = 0;

	static void scriptRegister(lua_State * L);
	
};