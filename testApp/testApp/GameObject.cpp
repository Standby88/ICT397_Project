#include "GameObject.h"

GameObject::GameObject()
{
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;

}

void GameObject::updateObject(float x, float y, float z)
{
	objectPos.x = x;
	objectPos.y = y;
	objectPos.z = z;
	std::cout << "gameObj" << std::endl;
}
glm::vec3 GameObject::getObjectPos()
{
	return objectPos;
}

void GameObject::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.beginClass<GameObject>("GameObject")
		.addConstructor<void(*) (void)>()
		.addFunction("updateObject", &GameObject::updateObject)
		.addFunction("getObjectPos", &GameObject::getObjectPos)
		.endClass()
		.endNamespace();
}