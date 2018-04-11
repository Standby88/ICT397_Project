#include "EnvironmentObjManager.h"



EnvironmentObjManager::EnvironmentObjManager()
{
}


EnvironmentObjManager::~EnvironmentObjManager()
{
	
	eOL::iterator itr;
	for (itr = environmentObjList.begin(); itr != environmentObjList.end(); ++itr)
	{
		delete itr->second;
	}
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

void EnvironmentObjManager::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("EOM")
		.beginClass<EnvironmentObjManager>("EnvironmentObjManager")
		.addConstructor<void(*) (void)>()
		.addFunction("addObject", &EnvironmentObjManager::addObject)
		.addFunction("drawAllObjects", &EnvironmentObjManager::DrawAllObjects)
		.addFunction("removeObject", &EnvironmentObjManager::removeObject)
		.addFunction("getObject", &EnvironmentObjManager::getObject)
		.endClass()
		.endNamespace();
}