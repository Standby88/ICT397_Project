#include "PhysicsFacade.h"

PhysicsFacade* PhysicsFacade::instance = 0;

PhysicsFacade::PhysicsFacade()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	
	overLappingPairCache = new btDbvtBroadphase();

	solver = new btSequentialImpulseConstraintSolver;
	
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overLappingPairCache, solver, collisionConfiguration);
	
	bodyID = 0;

	SetGravity(-9.8f);

}

PhysicsFacade::~PhysicsFacade()
{
	delete dynamicsWorld;

	delete solver;

	delete overLappingPairCache;

	delete dispatcher;

	delete collisionConfiguration;

	collisionShapes.clear();
}

PhysicsFacade* PhysicsFacade::GetPhysicsInstance()
{
	if (instance == 0) 
	{
		instance = new PhysicsFacade();
		std::cout << "First physicsfacade instance created" << std::endl;
	}
	
	return instance;
}

void PhysicsFacade::SetGravity(float grav)
{
	dynamicsWorld->setGravity(btVector3(0, grav, 0));
}

int PhysicsFacade::AssignObjectIndex()
{
	return bodyID++;
}

float PhysicsFacade::GetXPosition(int i)
{
	if (i < dynamicsWorld->getNumCollisionObjects())
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		trans = obj->getWorldTransform();
		return(trans.getOrigin().getX());
	}
}

float PhysicsFacade::GetYPosition(int i)
{
	if (i < dynamicsWorld->getNumCollisionObjects())
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		trans = obj->getWorldTransform();
		return(trans.getOrigin().getY());
	}
}

float PhysicsFacade::GetZPosition(int i)
{
	if (i < dynamicsWorld->getNumCollisionObjects())
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		trans = obj->getWorldTransform();
		return(trans.getOrigin().getZ());
	}
}

//uses a heightmap to generate a collidable terrain
rigidBody* PhysicsFacade::CreateHeightFieldRigidBody(
	int heightStickWidth, int heightStickLength,
	const void * heightfieldData, 
	float scaleHeight, int upAxis,
	bool useFloatData, bool flipQuadEdges)
{
	btScalar scaleH = (btScalar)scaleHeight;
	btCollisionShape* hFieldShape = new btHeightfieldTerrainShape(heightStickWidth, heightStickLength,
		heightfieldData, scaleH, upAxis, useFloatData, flipQuadEdges);
	this->collisionShapes.push_back(hFieldShape);

	btTransform terrainTransform;
	terrainTransform.setIdentity();

	terrainTransform.setOrigin(btVector3(0, 0, 0));

	btDefaultMotionState* hFieldMotionState = new btDefaultMotionState(terrainTransform);
	//has 0 mass, it's static, won't move.
	btRigidBody::btRigidBodyConstructionInfo hFieldRigidBodyCI(0, hFieldMotionState, hFieldShape, btVector3(0, 0, 0));
	btRigidBody* hFieldRigidBody = new btRigidBody(hFieldRigidBodyCI);

	if (heightfieldData)
	{
		std::cout << "HeightfieldData is not NULL" << std::endl;
	}

	hFieldRigidBody->setUserIndex(AssignObjectIndex());

	dynamicsWorld->addRigidBody(hFieldRigidBody);

	return hFieldRigidBody;
}

rigidBody* PhysicsFacade::CreateSphereRigidBody(float rad, float m, float xPos, float yPos, float zPos, float xIner, float yIner, float zIner)
{
	btCollisionShape* sphereShape = new btSphereShape((btScalar)rad);
	this->collisionShapes.push_back(sphereShape);

	btTransform sphereTransform;
	sphereTransform.setIdentity();

	sphereTransform.setOrigin(btVector3(xPos, yPos, zPos));

	btScalar mass(m);

	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(xIner, yIner, zIner);

	if (isDynamic)
	{
		sphereShape->calculateLocalInertia(mass, localInertia);
	}

	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(sphereTransform);
	btRigidBody::btRigidBodyConstructionInfo sphereRBCI(mass, sphereMotionState, sphereShape, localInertia);
	btRigidBody* sphereBody = new btRigidBody(sphereRBCI);

	sphereBody->setUserIndex(AssignObjectIndex());

	//dynamicsWorld->addRigidBody(sphereBody);
	std::cout << "hey boys" << std::endl;

	return sphereBody;
}

rigidBody* PhysicsFacade::CreateBoxRigidBody(int h, int w, int l, int m, int xPos, int yPos, int zPos)
{
	btCollisionShape* boxShape = new btBoxShape(btVector3(btScalar(w), btScalar(h), btScalar(l)));
	this->collisionShapes.push_back(boxShape);
	btTransform boxTransform;
	boxTransform.setIdentity();

	boxTransform.setOrigin(btVector3(xPos, yPos, zPos));
	btScalar boxMass(m);

	bool isDynamic = (boxMass != 0.f);

	btVector3 localInertia(0, 0, 0);

	if (isDynamic)
	{
		boxShape->calculateLocalInertia(boxMass, localInertia);
	}

	btDefaultMotionState* boxMotionState = new btDefaultMotionState(boxTransform);

	btRigidBody::btRigidBodyConstructionInfo groundRBCI(boxMass, boxMotionState, boxShape, localInertia);
	btRigidBody* boxBody = new btRigidBody(groundRBCI);

	boxBody->setUserIndex(AssignObjectIndex());

	//dynamicsWorld->addRigidBody(body);
	std::cout << "box made" << std::endl;

	return boxBody;
}

rigidBody* PhysicsFacade::CreatePlayerRigidBody(float radius, float height, float m, glm::vec3 pos, glm::vec3 iner)
{
	btCollisionShape* capsuleShape = new btCapsuleShape(radius, height);
	this->collisionShapes.push_back(capsuleShape);
	btTransform capsuleTransform;
	capsuleTransform.setIdentity();

	capsuleTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	btScalar capsuleMass(m);

	bool isDynamic = (capsuleMass != 0.f);

	btVector3 localInertia(btVector3(iner.x, iner.y, iner.z));

	if (isDynamic)
	{
		capsuleShape->calculateLocalInertia(capsuleMass, localInertia);
	}

	btDefaultMotionState* capsuleMotionState = new btDefaultMotionState(capsuleTransform);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(capsuleMass, capsuleMotionState, capsuleShape, localInertia);
	btRigidBody* capsuleRigidBody = new btRigidBody(fallRigidBodyCI);

	playerID = AssignObjectIndex();

	capsuleRigidBody->setUserIndex(playerID);

	playerPosition = btVector3(pos.x, pos.y, pos.z);

	//capsuleRigidBody->setGravity(btVector3(0, -10, 0));

	dynamicsWorld->addRigidBody(capsuleRigidBody);

	return capsuleRigidBody;
}

//not really use atm
/*int PhysicsFacade::CreateRigidBodyPlane(const PhysicsVector& planeNorm, float oSet)
{
	btCollisionShape* planeShape = new btStaticPlaneShape(btVector3(planeNorm.x, planeNorm.y, planeNorm.z), oSet);
	btVector3 planeNormal = btVector3(planeNorm.x, planeNorm.y, planeNorm.z);
	btScalar offSet = (btScalar)oSet;

	btDefaultMotionState* planeMotionShape = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(0, planeMotionShape, planeShape, btVector3(0, 0, 0));
	btRigidBody* planeRigidBody = new btRigidBody(planeRigidBodyCI);
	dynamicsWorld->addRigidBody(planeRigidBody);
	//collisionObjects.push_back(*planeRigidBody);
	return AssignObjectIndex();
}
//not really use atm
int PhysicsFacade::CreateFallingCylinderRigidBody(PhysicsVector& physVec)
{
	btCollisionShape* fallShape = new btCylinderShape(btVector3(physVec.x, physVec.y, physVec.z));
	
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	//collisionObjects.push_back(*fallRigidBody);
	return AssignObjectIndex();
}
//not really use atm
int PhysicsFacade::CreateFallingCapsuleRigidBody(float radius, float height)
{
	btCollisionShape* fallShape = new btCapsuleShape(radius, height);

	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	//collisionObjects.push_back(*fallRigidBody);
	return AssignObjectIndex();
}
//not really use atm
int PhysicsFacade::CreateFallingConeRigidBody(float radius, float height)
{
	btCollisionShape* fallShape = new btConeShape(radius, height);
	
	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
	//collisionObjects.push_back(*fallRigidBody);
	return AssignObjectIndex();
}*/


void PhysicsFacade::StepSimulation(float tStep, int maxSubSteps, V3 &playerPos)
{
	dynamicsWorld->stepSimulation(tStep, maxSubSteps);

	//update positions of all objects in dynamicsWorld
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;

		//reset forces on player before next step simulation
		if (body->getUserIndex() == playerID)
		{
			//body->clearForces();
			btVector3 tempV = body->getLinearVelocity();
			body->setLinearVelocity(btVector3(0, tempV.getY(), 0));
		}

		//update bodies
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			trans = obj->getWorldTransform();
		}

		//std::cout << "playerID " << playerID << std::endl;
		//std::cout << "body->getUserIndex() " << body->getUserIndex() << std::endl;
		//if current body is the player's body
		if (body->getUserIndex() == playerID)
		{
			//std::cout << "something" << std::endl;
			btVector3 playerP(btVector3(playerPos.x, playerPos.y, playerPos.z));
			playerForce.setX((playerP.getX() - playerPosition.getX()) * 100000);
			playerForce.setY((playerP.getY() - playerPosition.getY()) * 1000);
			playerForce.setZ((playerP.getZ() - playerPosition.getZ()) * 100000);

			body->applyCentralForce(playerForce);
			playerPosition = trans.getOrigin();
			//std::cout << "btx: " << float(trans.getOrigin().getX()) << std::endl;
			//std::cout << "bty: " << float(trans.getOrigin().getY()) << std::endl;
			//std::cout << "btz: " << float(trans.getOrigin().getZ()) << std::endl;
			//update parameter 
			playerPos.x = float(trans.getOrigin().getX());
			playerPos.y = float(trans.getOrigin().getY());
			playerPos.z = float(trans.getOrigin().getZ());

			//std::cout << "x after: " << playerPos.x << std::endl;
			//std::cout << "y after: " << playerPos.y << std::endl;
			//std::cout << "z after: " << playerPos.z << std::endl;


		}
		std::cout << "world pos object " << i << " " << float(trans.getOrigin().getX()) << " "
			<< float(trans.getOrigin().getY()) << " " << float(trans.getOrigin().getZ()) << std::endl;
	}
	
}

void PhysicsFacade::SetObjectActivation()
{
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		//force activation of all objects in dynamicsWorld
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		obj->forceActivationState(DISABLE_DEACTIVATION);
	}
}

void PhysicsFacade::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("PF")
		.beginClass<PhysicsFacade>("PhysicsFacade")
		.addConstructor<void(*) (void)>()
		.addStaticFunction("GetPhysicsInstance", &PhysicsFacade::GetPhysicsInstance)
		.addFunction("CreateHeightFieldRigidBody", &PhysicsFacade::CreateHeightFieldRigidBody)
		.addFunction("CreateSphereRigidBody", &PhysicsFacade::CreateSphereRigidBody)
		.addFunction("CreatePlayerRigidBody", &PhysicsFacade::CreatePlayerRigidBody)
		.addFunction("CreateBoxRigidBody", &PhysicsFacade::CreateBoxRigidBody)
		.addFunction("SetGravity", &PhysicsFacade::SetGravity)
		.addFunction("print", &PhysicsFacade::print)
		.endClass()
		.endNamespace();

	getGlobalNamespace(L)
		.beginNamespace("RB")
		.beginClass<rigidBody>("rigidBody")
		.endClass()
		.endNamespace();

}



