#pragma once

#include <map>
#include "GameAssetCreator.h"
#include <iostream>
#include "Player.h"
#include "WorldTerrain.h"
#include "EnvironmentObject.h"
/**
* @class GameAssetFactory
* @brief Used to create objects without hard code
* Objects creators are registered with a string mapped, then objects can be created by using that string identifier
*
* @author Desmond Ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
template <class T, class Key>
class GameAssetFactory
{
private:

	///stores create functions for different type of objects
	std::map<Key, BaseCreator<T>*> CreateFuncMap;
public:

	/**
	* @brief Register function used to register a create function and map it to a string
	*
	* @param Key Id, BaseCreator<T>* Fn
	*/
	void Register(Key Id, BaseCreator<T>* Fn)
	{
		std::cout << "registering" << std::endl;
		CreateFuncMap[Id] = Fn;
	}

	/**
	* @brief Create function is called from list 
	*
	* @param Key Id, BaseCreator<T>* Fn
	*/
	T* Create(Key funcName)
	{
		if (!CreateFuncMap.empty())
			std::cout << "not empty" << std::endl;
		return CreateFuncMap[funcName]->Create();
	}

	/**
	* @brief testing function
	*
	*/
	void Print()
	{
		std::cout << "printing" << std::endl;
	}

	/**
	* @brief release pointer to creators in the destructor
	*
	*/
	~GameAssetFactory()
	{
		typedef std::map<Key, BaseCreator<T>*>::iterator i;
		i itr;
		for (itr = CreateFuncMap.begin(); itr != CreateFuncMap.end(); ++itr)
		{
			delete itr->second;
		}

	}

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
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

