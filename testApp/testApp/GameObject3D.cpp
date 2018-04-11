#include "GameObject3D.h"

GameObject3D::GameObject3D()
{
}

std::string GameObject3D::getObjectType()
{
	return objectType;
}

Model * GameObject3D::getModel()
{
	return objectModel;
}

void GameObject3D::LoadModel(char * Path)
{
}

void GameObject3D::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<GameObject3D,GameObject>("GameObject")
		//.addConstructor<void(*) (void)>()
		.addFunction("LoadModel", &GameObject3D::LoadModel)
		.addFunction("getModel", &GameObject3D::getModel)
		.addFunction("getObjectType", &GameObject3D::getObjectType)
		.endClass()
		.endNamespace();
}


