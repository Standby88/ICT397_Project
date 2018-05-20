#include "ModelManager.h"



ModelManager::ModelManager()
{
}

ModelManager & ModelManager::GetModelManager()
{
	ModelManager * modelMan = NULL;

	if (modelMan == NULL)
	{
		modelMan = new ModelManager();
	}

	return *modelMan;
}


bool ModelManager::addModel(std::string modelPath)
{
	
	if (models.count(modelPath) != 1)
	{
		Model* temp = new Model(modelPath);
		models[modelPath] = temp;
		return true;
	}
	return false;
}

Model* ModelManager::GetModel(std::string modelPath)
{
	map<std::string, Model *>::iterator it = models.begin();

	while (it != models.end())
	{
		if (models[modelPath]->getName().compare(modelPath) == 0)
		{

			return models.at(modelPath);
		}
			
	}

	return NULL;
}

void ModelManager::destroyModelManager()
{
	ModelManager *modelMan = &GetModelManager();

	if (modelMan != NULL)
		delete modelMan;
}

void ModelManager::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("MM")
		.beginClass<ModelManager>("ModelManager")
		.addConstructor<void(*)(void)>()
		.addFunction("addModel", &ModelManager::addModel)
		.addFunction("GetModel", &ModelManager::GetModel)
		.addStaticFunction("GetModelManager", &ModelManager::GetModelManager)
		.addFunction("destroyModelManager", &ModelManager::destroyModelManager)
		.endClass()
		.endNamespace();
}

ModelManager::~ModelManager()
{

}
