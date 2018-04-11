#include "CharacterManager.h"



CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
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
