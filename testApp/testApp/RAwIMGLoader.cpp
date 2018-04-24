#include "RawIMGLoader.h"

unsigned char * RawIMGLoader::loadRaw(const char * filename, const int size)
{
	unsigned char * data = NULL;
	std::ifstream infile(filename, std::ios::binary);
	if (!infile) {
		std::cout << "Cannot open file :" << filename << std::endl;
		return false;
	}
	//allocate memory
	if (data)
		delete[] data;
	if (size>0)
		data = new unsigned char[size*size];
	if (data == NULL)
		return false;
	//read in heightfield.
	// get length of file:
	infile.seekg(0, std::ios::end);
	int length = infile.tellg();
	// read data as a block:
	infile.seekg(0, std::ios::beg);
	infile.read(reinterpret_cast<char *>(data), length);
	infile.close();

	return data;
}
