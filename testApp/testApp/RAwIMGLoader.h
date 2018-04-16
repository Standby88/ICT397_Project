#pragma once
#include <iostream>
#include <fstream>

/**
* @class RawIMGLoader
* @brief used to load raw file for heightfield
*
* @author Desmond
* @version 1
* @date
*
* @todo
*
* @bug
*/
class RawIMGLoader
{
public:

	/**
	* @brief load a raw file and return a char* array representing that file
	*
	*@param const char *filename, const int size
	*@return unsigned char*
	*/
	static unsigned char* loadRaw(const char *filename, const int size);
};

