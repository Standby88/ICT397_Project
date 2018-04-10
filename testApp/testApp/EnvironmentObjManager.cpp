#include "EnvironmentObjManager.h"



EnvironmentObjManager::EnvironmentObjManager()
{
}


EnvironmentObjManager::~EnvironmentObjManager()
{
}

void EnvironmentObjManager::addObject(EnvironmentObject & in)
{
	eOL.push_back(in);
}
