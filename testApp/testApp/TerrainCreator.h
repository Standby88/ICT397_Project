#pragma once
#include "GameAssetCreator.h"
template <class DerivedType, class BaseType>
class TerrainCreator : public GameAssetCreator<BaseType>
{
public:
	TerrainCreator() {};
	~TerrainCreator() {};

	BaseType* Create()
	{
		return new DerivedType;
	}
	
};