/*
* PhysicsFacade.h - PhysicsFacade class declaration
*
*  Created on: 1 April 2018
*      Author: Kieron van der Kwast 32230384
*/

//---------------------------------------------------------------------------------

#pragma once

/*extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include <LuaBridge.h>*/

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
#include "BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include "BulletDynamics\Character\btKinematicCharacterController.h"
#include <vector>
#include <iostream>	//only included to check values

typedef struct PhysicsVector
{
	PhysicsVector(float xCoord, float yCoord, float zCoord)
	{
		x = xCoord;
		y = yCoord;
		z = zCoord;
	}

	float x;
	float y;
	float z;
};

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
* @todo complete the facade
* @todo make sure the functions to create necessary collision bodies are working
*
* @bug none
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
	/*
	//std::vector<btCollisionObject> collisionObjects;

	btKinematicCharacterController* playerCharacter;
	btConvexShape* pShape;
	btRigidBody* pBody;*/


	//int bodyIndex;

	/**
	* @brief
	*
	*
	*
	* @param
	* @return
	* @pre
	* @post
	*/
	//int AssignObjectIndex();

public:
		///Default constructor to initiailise class member variables
	PhysicsFacade();
		///Default destructor to free memory
	~PhysicsFacade();

	/**
	* @brief Sets the gravity
	*
	*	
	*
	* @param float
	* @return void
	* @pre
	* @post
	*/
	void SetGravity(float grav);

	//PhysicsFacade(PhysicsFacade const &) = delete;

	//static PhysicsFacade& GetInstance();

	/**
	* @brief
	*
	*
	*
	* @param
	* @return
	* @pre
	* @post
	*/
	//void InitPhysics(PhysicsVector& grav);

	//void CharacterSetup(float charW, float charH, float xPosition, float yPosition, float zPosition, float mass);

	/**
	* @brief
	*
	*
	*
	* @param
	* @return
	* @pre
	* @post
	*/
	//int CreateKinematicCharacter();

	/**
	* @brief 
	*
	*
	*
	* @param
	* @return
	* @pre
	* @post
	*/
	int CreateRigidBodyPlane(const PhysicsVector& planeNorm, float offset);

	/**
	* @brief Takes in a height field and creates a rigid body
	*
	* 
	*
	* @param int, int, const void*, float, int, bool, bool
	* @return void 
	* @pre
	* @post
	*/
	void CreateHeightFieldRigidBody(int heightStickWidth, int heightStickLength,
		const void * heightfieldData, float scaleHeight, int upAxis,
		bool useFloatData, bool flipQuadEdges);

	/**
	* @brief Creates a spherical rigid body
	*
	*
	*
	* @param float, float, float, float, float, float, float, float
	* @return void
	* @pre
	* @post
	*/
	void CreateSphereRigidBody(float radius, float mass, float xPosition, float yPosition, float zPosition, 
		float xInertia, float yInertia, float zInertia);

	/**
	* @brief Creates a box shaped rigid body
	*
	*
	*
	* @param int, int, int, int, int, int, int, int, int, int
	* @return
	* @pre
	* @post
	*/
	void CreateRigidBodyBox(int height, int width, int length, int mass, int xPosition, int yPosition, int zPosition, int xInertia, int yInertia, int zInertia);

	/**
	* @brief 
	*
	*
	*
	* @param
	* @return
	* @pre
	* @post
	*/
	int CreateFallingCylinderRigidBody(PhysicsVector& physVec);

	/**
	* @brief
	*
	*
	*
	* @param
	* @return
	* @pre
	* @post
	*/
	int CreateFallingCapsuleRigidBody(float radius, float height);

	/**
	* @brief
	*
	*
	*
	* @param
	* @return
	* @pre
	* @post
	*/
	int CreateFallingConeRigidBody(float radius, float height);


	//void AddRigidBody(btRigidBody* body);

	//void RemoveRigidBody(btRigidBody* body);

	//void RemoveCollisionShape(btCollisionShape* colShape);

	void CharacterMovement(int characterIndex, float dt, int moveDirection);

	/**
	* @brief Updates the rigid bodies within the world
	*
	*
	*
	* @param float, int
	* @return void
	* @pre
	* @post
	*/
	void StepSimulation(float tStep, int maxSubSteps);

	/**
	* @brief Returns the X value of a body
	*
	*
	*
	* @param int
	* @return float
	* @pre
	* @post
	*/
	float GetXOrigin(int i);

	/**
	* @brief Returns the Y value of a body
	*
	*
	*
	* @param int 
	* @return float
	* @pre
	* @post
	*/
	float GetYOrigin(int i);

	/**
	* @brief Returns the Z value of a body
	*
	*
	*
	* @param int 
	* @return float
	* @pre
	* @post
	*/
	float GetZOrigin(int i);

	/**
	* @brief Exposes the class methods to Lua
	*
	*
	*
	* @param lua_state*
	* @return void
	* @pre
	* @post
	*/
	//void scriptRegister(lua_state * L);

};

