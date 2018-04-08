#pragma once
#include "GameAssetCreator.h"
template <class DerivedType, class BaseType>
class CharacterCreator : public GameAssetCreator<BaseType>
{
public:
	BaseType* Create()
	{
		return new DerivedType;
	}
};