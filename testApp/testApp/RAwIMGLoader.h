#pragma once
#include <iostream>
#include <fstream>
class RawIMGLoader
{
public:
	static unsigned char* loadRaw(const char *filename, const int size);
};

