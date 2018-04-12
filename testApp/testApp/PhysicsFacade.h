#pragma once

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
#include "BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include <list>
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

class PhysicsFacade
{
private:

	btBroadphaseInterface* broadphase;
	
	btDefaultCollisionConfiguration* collisionConfiguration;
	
	btCollisionDispatcher* dispatcher;
	
	btSequentialImpulseConstraintSolver* solver;
	
	btDiscreteDynamicsWorld* dynamicsWorld;

	std::list<btRigidBody> rigidBodies;

public:
	PhysicsFacade();
	
	~PhysicsFacade();

	//PhysicsFacade(PhysicsFacade const &) = delete;

	//static PhysicsFacade& GetInstance();

	void InitGravity(PhysicsVector& grav);

	void CreateStaticRigidPlane(const PhysicsVector& planeNorm, float offset);

	void CreateFallingSphereRigidBody(float radius);

	void CreateFallingBoxRigidBody(PhysicsVector& physVec);

	void CreateFallingCylinderRigidBody(PhysicsVector& physVec);

	void CreateFallingCapsuleRigidBody(float radius, float height);

	void CreateFallingConeRigidBody(float radius, float height);

	void CreateHeightFieldRigidBody(int heightStickWidth, int heightStickLength,
							const void * heightfieldData, float scaleHeight, int upAxis,
							bool useFloatData, bool flipQuadEdges);

	//void AddRigidBody(btRigidBody* body);

	//void RemoveRigidBody(btRigidBody* body);

	//void RemoveCollisionShape(btCollisionShape* colShape);

	void StepSimulation(float tStep, int maxSubSteps);

};

