#include "PhysicsFacade.h"

PhysicsFacade::PhysicsFacade()
{
		//broadphase is important if world will have a lot of rigid bodies
	this->broadphase = new btDbvtBroadphase();
		//broadphase is an excellent place for eliminating object pairs that should not collide
		//The collision configuration allows fine tuning of algorithms used for the full (not broadphase)
		//collision detection
	this->collisionConfiguration = new btDefaultCollisionConfiguration();
	this->dispatcher = new btCollisionDispatcher(collisionConfiguration);
		//if we introduce different types of collision objects later (eg meshes using gtGImpactMeshShape)
		//then we may need to register a collision algorithm to get collisions recognised
	btGImpactCollisionAlgorithm::registerAlgorithm(this->dispatcher);
		//we need a "solver". This is what causes the objects to intereact properly
	this->solver = new btSequentialImpulseConstraintSolver;
		//now we can instantiate the dynamics world
	this->dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	rigidBodies;
}

PhysicsFacade::~PhysicsFacade()
{
	delete this->dynamicsWorld;
	delete this->solver;
	delete this->dispatcher;
	delete this->collisionConfiguration;
	delete broadphase;
}

/*PhysicsFacade& PhysicsFacade::GetInstance()
{
	static PhysicsFacade instance;

	return instance;
}*/

void PhysicsFacade::InitGravity()
{
	dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void PhysicsFacade::CreateStaticRigidPlane(const btVector3& planeNormal, btScalar offset)
{
	btCollisionShape* planeShape =  new btStaticPlaneShape(planeNormal, offset);
	btDefaultMotionState* planeMotionShape = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(0, planeMotionShape, planeShape, btVector3(0, 0, 0));
	btRigidBody* planeRigidBody = new btRigidBody(planeRigidBodyCI);
	dynamicsWorld->addRigidBody(planeRigidBody);
	rigidBodies.push_back(*planeRigidBody);
}

void PhysicsFacade::CreateFallingRigidBody(btCollisionShape* fallShape)
{
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	rigidBodies.push_back(*fallRigidBody);
}

void PhysicsFacade::AddRigidBody(btRigidBody* body)
{
	dynamicsWorld->addRigidBody(body);
}

void PhysicsFacade::RemoveRigidBody(btRigidBody* body)
{
	dynamicsWorld->removeRigidBody(body);
	delete body->getMotionState();
	delete body;
}

void PhysicsFacade::RemoveCollisionShape(btCollisionShape* colShape)
{
	delete colShape;
}

void PhysicsFacade::StepSimulation(btScalar timeStep, int maxSubSteps)
{
	dynamicsWorld->stepSimulation(timeStep, maxSubSteps);
	btTransform trans;
	for (std::list<btRigidBody>::iterator it = rigidBodies.begin(); it != rigidBodies.end(); it++)
	{
		it->getMotionState()->getWorldTransform(trans);

		std::cout << "sphere height " << trans.getOrigin().getY() << std::endl;
	}

}


