#pragma once

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
#include "BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include <list>
#include <iostream>	//only included to check values
/**
* @class PhysicsVector
* @brief stores vector info to be converted to bullet vectores
*
* @author Kieron
* @version 1
* @date
*
* @todo
*
* @bug
*/
typedef struct PhysicsVector
{
	/**
	* @brief Constructor used to initialise vector with values
	*
	*@param float xCoord, float yCoord, float zCoord
	*/
	PhysicsVector(float xCoord, float yCoord, float zCoord)
	{
		x = xCoord;
		y = yCoord;
		z = zCoord;
	}

	///vector position values
	float x;
	float y;
	float z;
};

/**
* @class PhysicsFacade
* @brief Facade used to encapsulate bullet phys lib
*
* @author Kieron
* @version 1
* @date
*
* @todo
*
* @bug
*/
class PhysicsFacade
{
private:

	///Bullet variables used for storing physics information
	btBroadphaseInterface* broadphase;
	
	btDefaultCollisionConfiguration* collisionConfiguration;
	
	btCollisionDispatcher* dispatcher;
	
	btSequentialImpulseConstraintSolver* solver;
	
	btDiscreteDynamicsWorld* dynamicsWorld;

	///list of collision shapes
	std::list<btRigidBody> rigidBodies;

public:

	/**
	* @brief Constructor for physics facade
	*/
	PhysicsFacade();
	
	/**
	* @brief destructor for physics facade
	*
	*/
	~PhysicsFacade();

	//PhysicsFacade(PhysicsFacade const &) = delete;

	//static PhysicsFacade& GetInstance();

	/**
	* @brief initialise gravity direction
	*
	*@param PhysicsVector& grav
	*/
	void InitGravity(PhysicsVector& grav);

	/**
	* @brief create a plane used for simulation
	*
	*@param const PhysicsVector& planeNorm, float offset
	*/
	void CreateStaticRigidPlane(const PhysicsVector& planeNorm, float offset);

	/**
	* @brief create a sphere rigid bady
	*
	*@param float radius
	*/
	void CreateFallingSphereRigidBody(float radius);

	/**
	* @brief create a box rigid bady
	*
	*@param PhysicsVector& physVec
	*/
	void CreateFallingBoxRigidBody(PhysicsVector& physVec);

	/**
	* @brief create a cylinder rigid bady
	*
	*@param PhysicsVector& physVec
	*/
	void CreateFallingCylinderRigidBody(PhysicsVector& physVec);

	/**
	* @brief create a capsule rigid bady
	*
	*@param float radius, float height
	*/
	void CreateFallingCapsuleRigidBody(float radius, float height);

	/**
	* @brief create a cone rigid bady
	*
	*@param float radius, float height
	*/
	void CreateFallingConeRigidBody(float radius, float height);

	/**
	* @brief create a field rigid bady
	*
	*@param int heightStickWidth, int heightStickLength, const void * heightfieldData, float scaleHeight, int upAxis, bool useFloatData, bool flipQuadEdges
	*/
	void CreateHeightFieldRigidBody(int heightStickWidth, int heightStickLength,
							const void * heightfieldData, float scaleHeight, int upAxis,
							bool useFloatData, bool flipQuadEdges);

	//void AddRigidBody(btRigidBody* body);

	//void RemoveRigidBody(btRigidBody* body);

	//void RemoveCollisionShape(btCollisionShape* colShape);
	/**
	* @brief ends physics simulation
	*
	*@param int float tStep, int maxSubSteps
	*/
	void StepSimulation(float tStep, int maxSubSteps);

};

