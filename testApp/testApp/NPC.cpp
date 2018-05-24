#include "NPC.h"



NPC::NPC()
{
	objectType = "CharacterObj";
	objectPos.x = 0;
	objectPos.y = 0;
	objectPos.z = 0;
	objectModel = NULL;
	anim = false;

	m_StateMachine = new StateMachine<NPC>(this);

	m_StateMachine->SetCurrentState(Idle::Instance());
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

void NPC::ChangeState(State<NPC> *s)
{
	if (m_StateMachine->CurrentState() != s)
	{
		m_StateMachine->ChangeState(s);
	}
}

NPC * NPC::convert(GameObject * a)
{
	return dynamic_cast<NPC*>(a);
}

V3 NPC::getIdlePos()
{
	return this->m_IdlePos;
}

void NPC::setIdlePos(V3 newPos)
{
	this->m_IdlePos = newPos;
}

void NPC::setIdlePos(float x, float y, float z)
{
	V3 temp(x, y, z);

	this->m_IdlePos = temp;
}

V3 NPC::getMovePos()
{
	return this->m_movePos;
}

void NPC::setMovePos(V3 newPos)
{
	this->m_movePos = newPos;
}

void NPC::setMovePos(float x, float y, float z)
{
	V3 temp(x, y, z);

	this->m_movePos = temp;
}
