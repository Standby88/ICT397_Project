#pragma once
#include <unordered_map>
#include "Player.h"
class CharacterManager
{
private:
	Player* p;
	typedef std::unordered_map<std::string, int* > NPCL;
	NPCL nPCList;
public:
	CharacterManager();
	~CharacterManager();
	void addPlayer(GameObject* in);
	void addNPC(std::string key, int* in );
	/*void CharacterManager::DrawPlayer(Shader & S)
	{
		p->Draw(S);
	}*/
	/*void CharacterManager::DrawNPCs(Shader & s)
	{
	NPCL::iterator itr;
	for (itr = nPCList.begin(); itr != nPCList.end(); ++itr)
	{
		(*itr).second->Draw();
	}
	}*/
	void drawPlayer();
	void CharacterManager::drawNPCs();
	Player* getPlayer();
	int* getNPC(std::string);
	void removeNPC(std::string);
	void removePlayer();
	static void scriptRegister(lua_State * L);
	
};

