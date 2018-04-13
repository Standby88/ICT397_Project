#include "ModelManager.h"



ModelManager::ModelManager()
{
}


bool ModelManager::AddModel(char * modelPath)
{

	if (models.count(modelPath) != 1)
	{
		Model* temp = new Model(modelPath);
		//models.insert(std::pair<std::string, Model*>(modelPath, temp));
		models[modelPath] = temp;
		return true;
	}
	return false;
}

Model ModelManager::GetModel(char * modelPath)
{
	map<std::string, Model *>::iterator it = models.begin();

	while (it != models.end())
	{
		//std::cout << "Model at ";
		//std::cout << models[modelPath]->getName() << endl;
		if(strcmp(models[modelPath]->getName(), modelPath) == 0)
			return *models.at(modelPath);
	}

	return NULL;
}

ModelManager::~ModelManager()
{
}
