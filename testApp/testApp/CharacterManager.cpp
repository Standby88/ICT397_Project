#include "CharacterManager.h"



CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
	p = NULL;
	delete p;
	std::unordered_map<std::string, NPC* >::iterator itr;
	for (itr = nPCList.begin(); itr != nPCList.end(); ++itr)
	{
		itr->second = nullptr;
		delete itr->second;
	}
}

void CharacterManager::addPlayer(GameObject * in)
{
	Player*pl = dynamic_cast<Player*>(in);
	p = pl;
}

void CharacterManager::addNPC(GameObject * in,  std::string key)
{
	NPC*c = dynamic_cast<NPC*>(in);
	typedef std::pair<std::string,NPC*> temp;
	nPCList.insert(temp(key,c));
}


void CharacterManager::DrawPlayer(Shader & S)
{
	p->Draw(S);
}
void CharacterManager::drawNPCs(Shader &s)
{
	std::unordered_map<std::string, NPC* >::iterator itr;
	for (itr = nPCList.begin(); itr != nPCList.end(); ++itr)
	{
		(*itr).second->Draw(s);
	}
}

Player * CharacterManager::getPlayer()
{
	return p;
}

NPC * CharacterManager::getNPC(std::string K)
{
	return nPCList[K];
}

void CharacterManager::removeNPC(std::string K)
{
	nPCList.erase(K);
}



void CharacterManager::removePlayer()
{
	p = NULL;
}

void CharacterManager::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("CM")
		.beginClass<CharacterManager>("CharacterManager")
		.addConstructor<void(*) (void)>()
		.addFunction("addPlayer", &CharacterManager::addPlayer)
		.addFunction("addNPC", &CharacterManager::addNPC)
		.addFunction("drawPlayer", &CharacterManager::DrawPlayer)
		.addFunction("drawNPC", &CharacterManager::drawNPCs)
		.addFunction("getPlayer", &CharacterManager::getPlayer)
		.addFunction("getNPC", &CharacterManager::getNPC)
		.addFunction("removeNPC", &CharacterManager::removeNPC)
		.addFunction("removePlayer", &CharacterManager::removePlayer)
		.endClass()
		.endNamespace();
}

std::unordered_map<std::string, NPC*>& CharacterManager::getCharMap()
{
	return nPCList;
}
