#include "NPC_States.h"




Idle * Idle::FindInstance(NPC * npc)
{
	static Idle instance;

	return &instance;
}

void Idle::Enter(NPC * npc)
{
	if (npc->getObjectPos() != npc->getIdlePos())
	{
		//enter MOVE state to move to the Idle position

	}
}

void Idle::Execute(NPC * npc)
{
	//get idle time
	
	//decrease temp idle time

	//execute animation
}

void Idle::Exit(NPC * npc)
{
	//finished idling
}

Move * Move::FindInstance(NPC * npc)
{
	static Move move;
	return &move;
}

void Move::Enter(NPC * npc)
{
	//get target position

	if (npc->getMovePos)
	{

	}
}

void Move::Execute(NPC * npc)
{
	//translate closer to target position

	//perform animation
}

void Move::Exit(NPC * npc)
{
}
