#include "EnvironmentObjManager.h"



EnvironmentObjManager::EnvironmentObjManager()
{
}


EnvironmentObjManager::~EnvironmentObjManager()
{
}

void EnvironmentObjManager::addObject(EnvironmentObject * in, std::string key)
{
	typedef std::pair<std::string, EnvironmentObject*> temp;
	environmentObjList.insert(temp(key, in));
}

void EnvironmentObjManager::DrawAllObjects()
{
	eOL::iterator itr;
	for (itr = environmentObjList.begin(); itr != environmentObjList.end(); ++itr)
	{
		std::cout<<(*itr).second->getObjectType()<<endl;
	}


}

void EnvironmentObjManager::removeObject(std::string k)
{
	environmentObjList.erase(k);
}

EnvironmentObject * EnvironmentObjManager::getObject(std::string k)
{
	return environmentObjList[k];
}
