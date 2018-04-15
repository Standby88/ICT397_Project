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

	bool addModel(std::string modelPath/*char * modelPath*/);

	Model* GetModel(std::string modelPath);

	static ModelManager & GetModelManager();

	void destroyModelManager();

	void print()
	{
		std::cout << "hello" << std::endl;
	}

	static void scriptRegister(lua_State * L);


private:
	std::map<std::string, Model *> models;

};

