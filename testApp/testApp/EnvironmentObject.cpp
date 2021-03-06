#include "EnvironmentObject.h"

EnvironmentObject::EnvironmentObject()
{
	objectType = "EnvironmentObjType";
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;
	scale.x = 1;
	scale.y = 1;
	scale.z = 1;
	objectModel = NULL;
	angle = 0.0f;
	rotateAxis.x = 0.0f;
	rotateAxis.y = 0.0f;
	rotateAxis.z = 0.0f;
	isStatic = false;
}

EnvironmentObject::~EnvironmentObject()
{
	objectModel = NULL;
	delete objectModel;
}

void EnvironmentObject::Draw(Shader &S)
{
	objectModel->Draw(S);
}
void EnvironmentObject::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<EnvironmentObject, GameObject3D>("EnvironmentObject")
		.addConstructor<void(*) (void)>()
		.addFunction("Draw", &EnvironmentObject::Draw)
		.addFunction("convert", &EnvironmentObject::convert)
		.addFunction("setStatic", &EnvironmentObject::setStatic)
		.endClass()
		.endNamespace();
}

EnvironmentObject * EnvironmentObject::convert(GameObject * a)
{
	return dynamic_cast<EnvironmentObject*>(a);
}