#include "EnvironmentObject.h"

EnvironmentObject::EnvironmentObject()
{
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;
	objectModel = NULL;
}

void EnvironmentObject::Draw(Shader S)
{
	objectModel->Draw(S);
}
void EnvironmentObject::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<EnvironmentObject, GameObject>("Enemy")
		.addConstructor<void(*) (void)>()
		.addFunction("Draw", &EnvironmentObject::Draw)
		.endClass()
		.endNamespace();
}