#include "CharacterManager.h"



CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
}

void CharacterManager::addObject(GameObject3D & in)
{
	cOL.push_back(in);
}
