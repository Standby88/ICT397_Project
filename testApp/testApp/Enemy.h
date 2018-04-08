#pragma once

#include "Character.h"
class Enemy : public Character
{
public:
	std::string getName()
	{
		return "Enemy";
	}
};
