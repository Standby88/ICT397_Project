#pragma once
#include <string>
class Character
{
public:
	virtual ~Character() {};

	virtual std::string getName() = 0;
};