#pragma once
#include <vector>
#include "Player.h"
class CharacterManager
{
private:
	Player p;
	//std::vector<NPC> NPCList;
public:
	CharacterManager();
	~CharacterManager();
	void addObject(GameObject3D& in);
	void DrawPlayer(Shader S)
	{
		p.Draw(S);
	}
	void DrawNPC(Shader S)
	{

	}
};

