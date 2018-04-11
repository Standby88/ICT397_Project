#include "EnvironmentObjManager.h"



EnvironmentObjManager::EnvironmentObjManager()
{
}


EnvironmentObjManager::~EnvironmentObjManager()
{
}

void EnvironmentObjManager::addObject(GameObject * in, std::string key)
{
	EnvironmentObject * item = dynamic_cast<EnvironmentObject*>(in);
	typedef std::pair<std::string, EnvironmentObject*> temp;
	environmentObjList.insert(temp(key, item));
}

void EnvironmentObjManager::DrawAllObjects()
{
	eOL::iterator itr;
	for (itr = environmentObjList.begin(); itr != environmentObjList.end(); ++itr)
	{
		std::cout<<(*itr).second->getObjectType()<<std::endl;
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
