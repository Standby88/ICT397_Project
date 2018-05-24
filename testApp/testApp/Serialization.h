#pragma once
#include "cereal/archives/xml.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include <fstream>
#include <iostream>
class Serialization
{
private:

public:
	template<class T>
	static void saveData(T& data, std::string fileName)
	{
		std::ofstream os(fileName);
		cereal::XMLOutputArchive archive(os);
		archive(CEREAL_NVP(data));
	}
	template<class T>
	static T loadData(std::string fileName)
	{
		std::ifstream is(fileName);
		cereal::XMLInputArchive oarchive(is);
		T tempData;
		oarchive(tempData);

		return tempData;
	}
	Serialization();
	~Serialization();
};

