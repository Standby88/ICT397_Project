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

void GameObject3D::addModel(Model * model)
{
	objectModel = model;
}

void GameObject3D::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<GameObject3D,GameObject>("GameObject3D")
		//.addConstructor<void(*) (void)>()
		.addFunction("addModel", &GameObject3D::addModel)
		.addFunction("getModel", &GameObject3D::getModel)
		.addFunction("getObjectType", &GameObject3D::getObjectType)
		.endClass()
		.endNamespace();
}


