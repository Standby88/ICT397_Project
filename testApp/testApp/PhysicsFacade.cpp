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

void PhysicsFacade::InitGravity(PhysicsVector& grav)
{
	btVector3 gravity = btVector3(grav.x, grav.y, grav.z);
	dynamicsWorld->setGravity(gravity);
}

void PhysicsFacade::CreateStaticRigidPlane(const PhysicsVector& planeNorm, float oSet)
{
	btVector3 planeNormal = btVector3(planeNorm.x, planeNorm.y, planeNorm.z);
	btScalar offSet = (btScalar)oSet;
	btCollisionShape* planeShape =  new btStaticPlaneShape(planeNormal, offSet);
	btDefaultMotionState* planeMotionShape = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(0, planeMotionShape, planeShape, btVector3(0, 0, 0));
	btRigidBody* planeRigidBody = new btRigidBody(planeRigidBodyCI);
	dynamicsWorld->addRigidBody(planeRigidBody);
	rigidBodies.push_back(*planeRigidBody);
}

void PhysicsFacade::CreateHeightFieldRigidBody(int 	heightStickWidth, int heightStickLength,
	const void * heightfieldData, float scaleHeight, int upAxis,
	bool useFloatData, bool flipQuadEdges)
{
	btScalar scaleH = (btScalar)scaleHeight;
	btCollisionShape* hFieldShape = new btHeightfieldTerrainShape(heightStickWidth, heightStickLength,
		heightfieldData, scaleH, upAxis, useFloatData, flipQuadEdges);

	btDefaultMotionState* hFieldMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo hFieldRigidBodyCI(0, hFieldMotionState, hFieldShape, btVector3(0, 0, 0));
	btRigidBody* hFieldRigidBody = new btRigidBody(hFieldRigidBodyCI);
	dynamicsWorld->addRigidBody(hFieldRigidBody);
	rigidBodies.push_back(*hFieldRigidBody);
}

void PhysicsFacade::CreateFallingSphereRigidBody(float radius)
{
	btCollisionShape* fallShape = new btSphereShape((btScalar)radius);

	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	rigidBodies.push_back(*fallRigidBody);
}

void PhysicsFacade::CreateFallingBoxRigidBody(PhysicsVector& physVec)
{
	btCollisionShape* fallShape = new btBoxShape(btVector3(physVec.x, physVec.y, physVec.z));

	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	rigidBodies.push_back(*fallRigidBody);
}

void PhysicsFacade::CreateFallingCylinderRigidBody(PhysicsVector& physVec)
{
	btCollisionShape* fallShape = new btCylinderShape(btVector3(physVec.x, physVec.y, physVec.z));
	
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	rigidBodies.push_back(*fallRigidBody);
}

void PhysicsFacade::CreateFallingCapsuleRigidBody(float radius, float height)
{
	btCollisionShape* fallShape = new btCapsuleShape(radius, height);

	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	rigidBodies.push_back(*fallRigidBody);
}

void PhysicsFacade::CreateFallingConeRigidBody(float radius, float height)
{
	btCollisionShape* fallShape = new btConeShape(radius, height);
	
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	rigidBodies.push_back(*fallRigidBody);
}



/*void PhysicsFacade::AddRigidBody(btRigidBody* body)
{
	dynamicsWorld->addRigidBody(body);
}*/

/*void PhysicsFacade::RemoveRigidBody(btRigidBody* body)
{
	dynamicsWorld->removeRigidBody(body);
	delete body->getMotionState();
	delete body;
}*/

/*void PhysicsFacade::RemoveCollisionShape(btCollisionShape* colShape)
{
	delete colShape;
}*/

void PhysicsFacade::StepSimulation(float tStep, int maxSubSteps)
{
	btScalar timeStep = (btScalar)tStep;
	dynamicsWorld->stepSimulation(timeStep, maxSubSteps);
	btTransform trans;
	for (std::list<btRigidBody>::iterator it = rigidBodies.begin(); it != rigidBodies.end(); it++)
	{
		it->getMotionState()->getWorldTransform(trans);

		std::cout << "object height " << trans.getOrigin().getY() << std::endl;
	}

}


