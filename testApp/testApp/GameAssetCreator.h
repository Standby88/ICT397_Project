#pragma once

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>

/**
* @class BaseCreator
* @brief Used as an abstract class for other object creators
* 
*
* @author Desmond Ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
template <class T>
class BaseCreator
{
public:

	/**
	* @brief pure virtual constructor for BaseCreator
	*/
	virtual ~BaseCreator() {}

	/**
	* @brief virtual create function
	*/
	virtual T* Create() = 0;

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("GAC")
			.beginClass<BaseCreator<T>>("BaseCreator")
			.endClass()
			.endNamespace();
	}
};

template <class DerivedType, class BaseType>
class GameAssetCreator : public BaseCreator<BaseType>
{
public:
	/**
	* @brief Constructor for game assets
	*/
	GameAssetCreator() {};

	/**
	* @brief destructor for GameAssetCreator
	*/
	~GameAssetCreator() {};

	/**
	* @brief Create function used to create a new type of object and return a Gameobject pointer to that object
	*
	*@return baseType*
	*/
	BaseType* Create()
	{
		return new DerivedType;
	}

};