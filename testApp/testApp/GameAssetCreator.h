#pragma once

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
template <class T>
class BaseCreator
{
public:
	virtual ~BaseCreator() {}
	virtual T* Create() = 0;

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
	GameAssetCreator() {};
	~GameAssetCreator() {};

	BaseType* Create()
	{
		return new DerivedType;
	}

};