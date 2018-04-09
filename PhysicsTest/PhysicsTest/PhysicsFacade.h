#pragma once

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
#include <list>
#include <iostream>	//only included to check values

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

	void InitGravity();

	void CreateStaticRigidPlane(const btVector3& planeNorm, btScalar offset);

	void CreateFallingRigidBody(btCollisionShape* fallShape);

	void AddRigidBody(btRigidBody* body);

	void RemoveRigidBody(btRigidBody* body);

	void RemoveCollisionShape(btCollisionShape* colShape);

	void StepSimulation(btScalar timeStep, int maxSubSteps);

};

