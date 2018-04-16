#pragma once
#include <map>
#include <iostream>
#include <string>


#include "Model.h"
/**
* @class ModelManager
* @brief used to store and manages loaded models
*
* @author alex
* @version 1
* @date
*
* @todo
*
* @bug
*/
class ModelManager
{
public:

	/**
	* @brief Constructor for ModelManager
	*/
	ModelManager();

	/**
	* @brief destructor for Modelmanager
	*/
	~ModelManager();

	/**
	* @brief adds model to map using path as key.
	*@param string modelpath
	*@return bool
	*/
	bool addModel(std::string modelPath/*char * modelPath*/);

	/**
	* @brief returns a model from list
	*@param string modelpath
	*@return model*
	*/
	Model* GetModel(std::string modelPath);

	/**
	* @brief returns wholemodel maanager instance
	*@return modelManager&
	*/
	static ModelManager & GetModelManager();

	/**
	* @brief helper function used to release model data
	*/
	void destroyModelManager();

	/**
	* @brief expose functions to lua
	*@param lua_State * L
	*/
	static void scriptRegister(lua_State * L);


private:
	std::map<std::string, Model *> models;

};

