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
	void drawPlayer()
	{
		std::cout<<p->getObjectType()<<std::endl;
	}
	void CharacterManager::drawNPCs()
	{
		NPCL::iterator itr;
		for (itr = nPCList.begin(); itr != nPCList.end(); ++itr)
		{
			int * i = (*itr).second;
			std::cout<<*i<<std::endl;
		}
	}
	Player* getPlayer();
	int* getNPC(std::string);
	void removeNPC(std::string);
	void removePlayer();
	static void scriptRegister(lua_State * L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("CM")
			.beginClass<CharacterManager>("CharacterManager")
			.addConstructor<void(*) (void)>()
			.addFunction("addPlayer", &CharacterManager::addPlayer)
			.addFunction("addNPC", &CharacterManager::addNPC)
			.addFunction("drawPlayer", &CharacterManager::drawPlayer)
			.addFunction("drawNPC", &CharacterManager::drawNPCs)
			.addFunction("getPlayer", &CharacterManager::getPlayer)
			.addFunction("getNPC", &CharacterManager::getNPC)
			.addFunction("removeNPC", &CharacterManager::removeNPC)
			.addFunction("removePlayer", &CharacterManager::removePlayer)
			.endClass()
			.endNamespace();
	}
};

