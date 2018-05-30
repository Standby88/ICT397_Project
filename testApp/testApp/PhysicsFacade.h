/*
* PhysicsFacade.h - PhysicsFacade class declaration
*
*  Created on: 1 April 2018
*      Author: Kieron van der Kwast 32230384
*/

//---------------------------------------------------------------------------------

#pragma once

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
#include "BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include "MathLib.h"
#include <vector>
#include <iostream>	//only included to check values

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
#include <string>
#include <glm\glm.hpp>

using namespace luabridge;

//hide bullet specific rigidbodies behind a facade
typedef btRigidBody rigidBody;
//hide bullet specific quaternions behind a facade
typedef btQuaternion quaternion;

//---------------------------------------------------------------------------------

/**
* @class PhysicsFacade
* @brief Acts as a facade between client and a physics engine
*
* Holds several abstract methods used to create physics elements such as collision
* bodies and gravity.
*
* @author Kieron van der Kwast
* @version 01
* @date 1/04/2018 Kieron van der Kwast, Started,
*
* @author Kieron van der Kwast
* @version 02
* @date 24/04/2018 Trying to fix player rigid body movement problems
*
* @author Kieron van der Kwast
* @version 03
* @date 13/05/2018 Implementing new heightfield terrain function, implementing creation of capsule rigidbodies
*
* @author Kieron van der Kwast
* @version 04
* @date 26/05/2018 Implemented some set, get, and update functions so that specific bodies in the dynamicsWorld
					can be updated.
*
* @todo 
*
* @bug 
*/

//---------------------------------------------------------------------------------

class PhysicsFacade
{
private:
	/// btDefaultCollisionConfiguration object pointer
	btDefaultCollisionConfiguration* collisionConfiguration;
	/// btCollisionDispatcher object pointer
	btCollisionDispatcher* dispatcher;
	/// btBroadphaseInterface object pointer
	btBroadphaseInterface* overLappingPairCache;
	/// btSequentialImpulseConstraintSolver object pointer
	btSequentialImpulseConstraintSolver* solver;
	/// used to keep track of shapes
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	/// btDiscreteDynamicsWorld object pointer
	btDiscreteDynamicsWorld* dynamicsWorld;
	/// a persistent instance of PhysicsFacade
	static PhysicsFacade* instance;
	/// a vector for tracking a player's positon
	btVector3 playerPosition;
	/// a vector for storing forces acting on a player
	btVector3 playerForce;
	/// integer that stores the userIndex of a player rigidbody
	int playerID;
	/// integer that stores the index of a terrain rigidbody
	int terrainID;
	///	used to keep track of number of rigidbodies and to assign them a userIndex
	int bodyID;

	/**
	* @brief Used to keep track of number of objects in dynamicsWorld
	*
	* Each time an object is added to dynamicsWorld this will set its userIndex 
	*
	* @param void 
	* @return int
	* @pre
	* @post
	*/
	int AssignObjectIndex();

protected:

public:

	///Default constructor to initiailise class member variables
	PhysicsFacade();

	///Default destructor to free memory
	~PhysicsFacade();

	/**
	* @brief Used to get a single instance of PhysicsFacade
	*
	* @param void
	* @return PhysicsFacade*
	* @pre
	* @post
	*/
	static PhysicsFacade* GetPhysicsInstance();

	/**
	* @brief Sets the gravity
	*
	* @param float
	* @return void
	* @pre
	* @post
	*/
	void SetGravity(float grav);

	/**
	* @brief Gets X position of a rigidbody
	*
	* @param int
	* @return float
	* @pre
	* @post
	*/
	float GetXPosition(int index);

	/**
	* @brief Gets Y position of a rigidbody
	*
	* @param int
	* @return float
	* @pre
	* @post
	*/
	float GetYPosition(int index);

	/**
	* @brief Gets Z position of a rigidbody
	*
	* @param int
	* @return float
	* @pre
	* @post
	*/
	float GetZPosition(int index);

	/**
	* @brief gets quaternion for rotation of a rigidbody
	*
	* @param int
	* @return quaternion
	* @pre
	* @post
	*/
	quaternion GetRotation(int index);

	/**
	* @brief sets quaternion for rotation of a rigidbody
	*
	* @param int, quaternion*
	* @return void
	* @pre
	* @post
	*/
	void SetRotation(int index, quaternion* rotation);

	//Exclude dynamicsWorld->addRigidBody from Create.. functions functions as they are created 
	//in scripts, then added in constructors
	/**
	* @brief Adds a rigidbody to the dynamicsWorld
	*
	* @param rigidbody*
	* @return void
	* @pre
	* @post
	*/
	void AddRigidBody(rigidBody* body);

	/**
	* @brief Updates an existing rigidbody stored in dynamicsWorld
	*
	* @param rigidbody*
	* @return void
	* @pre
	* @post
	*/
	void UpdateRigidBody(rigidBody* body);

	/**
	* @brief currently not defined
	*
	* @param
	* @return
	* @pre
	* @post
	*/
	int CreateRigidBodyPlane(const V3 planeNorm, float offset);

	/**
	* @brief Takes in a height field and creates a rigid body
	*
	* @param int, int, const void*, float, int, bool, bool
	* @return void
	* @pre
	* @post
	*/
	rigidBody* CreateHeightFieldRigidBody(int heightStickWidth, int heightStickLength,
		const void * heightfieldData, float scaleWidth, float scaleHeight, float scaleLength,
		float heighestPoint, float lowestPoint);

	/**
	* @brief Creates a spherical rigid body
	*
	* @param float, float, float, float, float, float, float, float
	* @return void
	* @pre
	* @post
	*/
	rigidBody* CreateSphereRigidBody(float radius, float mass, float xPosition, float yPosition, float zPosition,
		float xInertia, float yInertia, float zInertia);

	/**
	* @brief Creates a box shaped rigid body
	*
	* @param int, int, int, int, int, int, int
	* @return rigidBody*
	* @pre
	* @post
	*/
	rigidBody* CreateBoxRigidBody(float height, float width, float length, float mass, float xPosition, float yPosition, float zPosition);

	/**
	* @brief creates a specific body for a player controlled rigidbody
	*
	* @param float, float, float, V3, V3
	* @return rigidBody*
	* @pre
	* @post
	*/
	rigidBody* CreatePlayerRigidBody(float radius, float height, float mass, V3 position, V3 inertia);

	/**
	* @brief creates a capsule body 
	*
	* @param float, float, float, float, float, float
	* @return rigidBody*
	* @pre
	* @post
	*/
	rigidBody* CreateCapsuleRigidBody(float radius, float height, float m, float xPos, float yPos, float zPos);

	/**
	* @brief Updates the rigid bodies within the world
	*
	* @param float, int
	* @return void
	* @pre
	* @post
	*/
	void StepSimulation(float tStep, int maxSubSteps, V3 &playerPos);

	/**
	* @brief Updates the rigid bodies within the world
	*
	* @param float, int
	* @return void
	* @pre
	* @post
	*/
	void SetObjectActivation();

	/**
	* @brief Exposes the class methods to Lua
	*
	* @param lua_state*
	* @return void
	* @pre
	* @post
	*/
	static void scriptRegister(lua_State * L);

	///Used for testing 
	void print() { std::cout << "printing" << std::endl; }

};

