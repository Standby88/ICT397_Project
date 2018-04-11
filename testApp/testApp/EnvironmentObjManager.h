#pragma once

#include <unordered_map>
#include "EnvironmentObject.h"
class EnvironmentObjManager
{
private:
	typedef std::unordered_map<std::string, EnvironmentObject* > eOL;
	eOL environmentObjList;
public:
	EnvironmentObjManager();
	~EnvironmentObjManager();
	void addObject(GameObject* in, std::string key);
	/*voidDrawAllObjects(Shader & S)
	{
		eOL::iterator itr;
		for (itr = environmentObjList.begin(); itr != environmentObjList.end(); ++itr)
		{
			(*itr).second->Draw(S) << endl;
		}
	}*/
	void DrawAllObjects();//test only
	void removeObject(std::string k);
	EnvironmentObject* getObject(std::string);
	static void scriptRegister(lua_State * L)
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

};

