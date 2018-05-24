#pragma once
#include "GameObject.h"
#include "Model.h"
#include "PhysicsFacade.h"

/**
* @class GameObject3D
* @brief USed as base for all objects that use 3D shaders
* 
*
* @author Desmond Ma
* @version 1
* @date
*
* @author Kieron van der Kwast
* @version 2
* @date 27/04/2018, Added PhysicsFacade instance, as well as a facaded rigidBody so all objects
					have a rigidBody. Also provided setter and getter methods for the rigidBody
*
* @todo
*
* @bug
*/
class GameObject3D : public GameObject
{
protected:

	///model pointer pointing to object that is assigned to an object
	Model * objectModel;

	///used to store what type of object the inherited type is
	std::string objectType;

	///facaded rigidbody variable
	rigidBody* gameObjBody;

public:

	/**
	* @brief Constructor for GameObject3D
	*/
	GameObject3D();

	/**
	* @brief Virtual destructor
	*
	*/
	virtual ~GameObject3D() {};

	/**
	* @brief Virtual draw function
	*
	*/
	virtual void Draw(Shader &S) = 0;

	/**
	* @brief return the type of object id
	*
	*@return string 
	*/
	std::string getObjectType();

	/**
	* @brief return pointer to model 
	*
	*@return Model*
	*/
	Model * getModel();

	/**
	* @brief load a model from file
	*
	*@param unsigned char * Path
	*/
	void addModel(Model* model);

	/**
	* @brief sets gameObjBody
	*
	*
	*
	* @param rigidBody*
	* @return void
	* @pre
	* @post
	*/
	void SetRigidBody(rigidBody* body);

	/**
	* @brief returns gameObjBody
	*
	*
	*
	* @param void
	* @return rigidBody*
	* @pre
	* @post
	*/
	rigidBody* GetRigidBody();

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);
};

