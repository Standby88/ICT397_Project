#pragma once
#include "cereal/archives/xml.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include <fstream>
#include <iostream>

/**
* @class Serialisation
* @brief used to manage serialisation
*
*
* @author Desmond ma
* @version 1
* @date
*
* @todo
*
* @bug
*/
class Serialization
{
private:

public:

	/**
	* @brief serialises data to file
	*
	* @param T&, std::string
	* @return void
	*/
	template<class T>
	static void saveData(T& data, std::string fileName)
	{
		std::ofstream os(fileName);
		cereal::XMLOutputArchive archive(os);
		archive(CEREAL_NVP(data));
	}

	/**
	* @brief deserialises data from file
	*
	* @param std::string
	* @return T
	*/
	template<class T>
	static T loadData(std::string fileName)
	{
		std::ifstream is(fileName);
		cereal::XMLInputArchive oarchive(is);
		T tempData;
		oarchive(tempData);

		return tempData;
	}

	///Default Constructor
	Serialization();

	///Default Destructor
	~Serialization();
};

