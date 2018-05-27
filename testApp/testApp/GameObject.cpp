#include "GameObject.h"

GameObject::GameObject()
{
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;
	scale.x = 1;
	scale.y = 1;
	scale.z = 1;

}

void GameObject::updateObject(float x, float y, float z)
{
	objectPos.x = x;
	objectPos.y = y;
	objectPos.z = z;
	//std::cout << "gameObj" << std::endl;
}

void GameObject::updateObjectRotation(float w, float x, float y, float z)
{
	angle = w;
	rotateAxis.x = x;
	rotateAxis.y = y;
	rotateAxis.z = z;
	//std::cout << "gameObj" << std::endl;
}

float GameObject::getObjectAngle()
{
	return angle;
}

V3 GameObject::getObjectRotation()
{
	return rotateAxis;
}

V3 GameObject::getObjectPos()
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
		.addFunction("updateObjectRotation", &GameObject::updateObjectRotation)
		.addFunction("ScaleObject", &GameObject::ScaleObject)
		.endClass()
		.endNamespace();
}