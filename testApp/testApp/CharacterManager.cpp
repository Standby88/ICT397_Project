#include "CharacterManager.h"



CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
	p = NULL;
	delete p;
	NPCL::iterator itr;
	for (itr = nPCList.begin(); itr != nPCList.end(); ++itr)
	{
		delete itr->second;
	}
}

void CharacterManager::addPlayer(GameObject * in)
{
	Player*pl = dynamic_cast<Player*>(in);
	p = pl;
}

void CharacterManager::addNPC(std::string key, int * in )
{
	typedef std::pair<std::string,int*> temp;
	nPCList.insert(temp(key, in));
}


void CharacterManager::drawPlayer()
{
	//std::cout << p->getObjectType() << std::endl;
}

void CharacterManager::drawNPCs()
{
	NPCL::iterator itr;
	for (itr = nPCList.begin(); itr != nPCList.end(); ++itr)
	{
		int * i = (*itr).second;
		std::cout << *i << std::endl;
	}
}

Player * CharacterManager::getPlayer()
{
	return p;
}

int * CharacterManager::getNPC(std::string K)
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
		.addFunction("drawPlayer", &CharacterManager::drawPlayer)
		.addFunction("drawNPC", &CharacterManager::drawNPCs)
		.addFunction("getPlayer", &CharacterManager::getPlayer)
		.addFunction("getNPC", &CharacterManager::getNPC)
		.addFunction("removeNPC", &CharacterManager::removeNPC)
		.addFunction("removePlayer", &CharacterManager::removePlayer)
		.endClass()
		.endNamespace();
}