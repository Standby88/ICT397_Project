#pragma once

#include <map>
#include "GameAssetCreator.h"
#include <iostream>
template <class T, class Key>
class GameAssetFactory
{
private:
	std::map<Key, GameAssetCreator<T>*> CreateFuncMap;
public:
	void Register(Key Id, GameAssetCreator<T>* Fn)
	{
		CreateFuncMap[Id] = Fn;
	}

	T* Create(Key funcName)
	{
		if (!CreateFuncMap.empty())
			std::cout << "not empty" << std::endl;
		return CreateFuncMap[funcName]->Create();
	}
	~GameAssetFactory()
	{
		std::map<Key, GameAssetCreator<T>*>::iterator i = CreateFuncMap.begin();
		while (i != CreateFuncMap.end())
		{
			delete i->second;
			++i;
		}
	};
};

