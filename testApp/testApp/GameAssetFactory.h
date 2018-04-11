#pragma once

#include <map>
#include "GameAssetCreator.h"
#include <iostream>
#include "Player.h"
#include "WorldTerrain.h"
#include "EnvironmentObject.h"

template <class T, class Key>
class GameAssetFactory
{
private:
	std::map<Key, BaseCreator<T>*> CreateFuncMap;
public:
	void Register(Key Id, BaseCreator<T>* Fn)
	{
		std::cout << "registering" << std::endl;
		CreateFuncMap[Id] = Fn;
	}

	T* Create(Key funcName)
	{
		if (!CreateFuncMap.empty())
			std::cout << "not empty" << std::endl;
		return CreateFuncMap[funcName]->Create();
	}
	void Print()
	{
		std::cout << "printing" << std::endl;
	}
	~GameAssetFactory()
	{
		typedef std::map<Key, BaseCreator<T>*>::iterator i;
		i itr;
		for (itr = CreateFuncMap.begin(); itr != CreateFuncMap.end(); ++itr)
		{
			delete itr->second;
		}

	}

	static void scriptRegister(lua_State * L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("GAF")
			.beginClass<GameAssetFactory<T, std::string>>("GameAssetFactory")
			.addConstructor<void(*) (void)>()
			.addFunction("Register", &GameAssetFactory<T, Key>::Register)
			.addFunction("Create", &GameAssetFactory<T, Key>::Create)
			.addFunction("Print", &GameAssetFactory<T, Key>::Print)
			.endClass()
			.endNamespace();
	}
};

