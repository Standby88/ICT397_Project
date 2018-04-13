#pragma once
#include <map>
#include <iostream>
#include <string>


#include "Model.h"

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	bool AddModel( char * modelPath);

	Model GetModel(char * modelPath);

private:
	map<std::string, Model *> models;

};

