#include "CharacterManager.h"



CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
}

void CharacterManager::addPlayer(Player * in)
{
	p = in;
}

void CharacterManager::addNPC(std::string key, int * in )
{
	typedef std::pair<std::string,int*> temp;
	nPCList.insert(temp(key, in));
}


Player * CharacterManager::getPlayer()
{
	return p;
}

int * CharacterManager::returnNPC(std::string K)
{
	return nPCList[K];
}

void CharacterManager::RemoveNPC(std::string K)
{
	nPCList.erase(K);
}

void CharacterManager::RemovePlayer()
{
	p = NULL;
}
