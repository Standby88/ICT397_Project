#include "NPC.h"



NPC::NPC()
{
	objectType = "CharacterObj";
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;
	objectModel = NULL;
	anim = false;
	skeleton = new Skeleton();
}


NPC::~NPC()
{
	objectModel = NULL;
	delete objectModel;
}

void NPC::Draw(Shader & S)
{
	if (anim == true)
	{
		UpdateSkeleton();
		objectModel->DrawAnimtated(S, this);
	}
	else
	{
		objectModel->Draw(S);
	}
	
}

void NPC::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<NPC, GameObject3D>("NPC")
		.addConstructor<void(*) (void)>()
		.addFunction("Draw", &NPC::Draw)
		.addFunction("convert", &NPC::convert)
		.endClass()
		.endNamespace();
}
NPC * NPC::convert(GameObject * a)
{
	return dynamic_cast<NPC*>(a);
}