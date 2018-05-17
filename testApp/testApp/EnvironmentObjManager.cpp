#include "EnvironmentObjManager.h"



EnvironmentObjManager::EnvironmentObjManager()
{
}


EnvironmentObjManager::~EnvironmentObjManager()
{
	
	std::unordered_map<std::string, EnvironmentObject* >::iterator itr;
	for (itr = environmentObjList.begin(); itr != environmentObjList.end(); ++itr)
	{
		itr->second = nullptr;
		delete itr->second;
	}
}

void EnvironmentObjManager::addObject(GameObject * in, std::string key)
{
	EnvironmentObject * item = dynamic_cast<EnvironmentObject*>(in);
	typedef std::pair<std::string, EnvironmentObject*> temp;
	environmentObjList.insert(temp(key, item));
}

void EnvironmentObjManager::drawAllObjects(Shader & S)
{
	std::unordered_map<std::string, EnvironmentObject* >::iterator itr;
	for (itr = environmentObjList.begin(); itr != environmentObjList.end(); ++itr)
	{
		(*itr).second->Draw(S);
	}
}
void EnvironmentObjManager::removeObject(std::string k)
{
	environmentObjList.erase(k);
}

EnvironmentObject * EnvironmentObjManager::getObject(std::string k)
{
	//std::cout << environmentObjList.size()<<std::endl;
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
		.addFunction("drawAllObjects", &EnvironmentObjManager::drawAllObjects)
		.addFunction("removeObject", &EnvironmentObjManager::removeObject)
		.addFunction("getObject", &EnvironmentObjManager::getObject)
		.endClass()
		.endNamespace();
}

std::unordered_map<std::string, EnvironmentObject*>& EnvironmentObjManager::getEnObjMap()
{
	return environmentObjList;;
}
