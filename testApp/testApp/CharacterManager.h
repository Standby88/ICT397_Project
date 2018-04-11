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
	void addPlayer(Player* in);
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
	void DrawPlayer()
	{
		std::cout<<p->getObjectType()<<std::endl;
	}
	void CharacterManager::DrawNPCs()
	{
		NPCL::iterator itr;
		for (itr = nPCList.begin(); itr != nPCList.end(); ++itr)
		{
			int * i = (*itr).second;
			std::cout<<*i<<std::endl;
		}
	}
	Player* getPlayer();
	int* returnNPC(std::string);
	void RemoveNPC(std::string);
	void RemovePlayer();
};

