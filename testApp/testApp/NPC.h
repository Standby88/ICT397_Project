#pragma once
#include "GameObject3D.h"
#include "StateMachine.h"
#include "NPC_States.h"
class NPC : public GameObject3D
{
private:
	StateMachine<NPC> * m_StateMachine;

	V3 m_IdlePos;
	V3 m_movePos;
public:
	NPC();
	~NPC();
	void Draw(Shader &S);
	static void scriptRegister(lua_State * L);
	NPC * convert(GameObject * a);

	V3 getIdlePos();
	void setIdlePos(V3 newPos);
	void setIdlePos(float x, float y, float z);

	V3 getMovePos();
	void setMovePos(V3 newPos);
	void setMovePos(float x, float y, float z);

	void ChangeState(State<NPC> *s);
};

