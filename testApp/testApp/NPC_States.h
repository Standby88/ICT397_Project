#ifndef NPC_STATES_H
#define NPC_STATES_H

#include "State.h"

class NPC;

class Idle : public State <NPC>
{
private:
	Idle * FindInstance(NPC * npc);
public:
	static Idle* Instance();

	virtual void Enter(NPC * npc);

	virtual void Execute(NPC * npc);

	virtual void Exit(NPC * npc);
};

class Move : public State <NPC>
{
private:
	Move * FindInstance(NPC * npc);
public:
	static Move *Instance();

	virtual void Enter(NPC* npc);

	virtual void Execute(NPC * npc);

	virtual void Exit(NPC *npc);
};

#endif