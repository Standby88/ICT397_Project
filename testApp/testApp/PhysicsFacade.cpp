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

	SetGravity(-25.8f);

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

quaternion PhysicsFacade::GetRotation(int i)
{
	return dynamicsWorld->getCollisionObjectArray()[i]->getWorldTransform().getRotation();
}

void PhysicsFacade::SetRotation(int i, quaternion* rot)
{
	dynamicsWorld->getCollisionObjectArray()[i]->getWorldTransform().setRotation(*rot);
}

void PhysicsFacade::AddRigidBody(rigidBody* body)
{
	if (body)
	{
		body->setUserIndex(AssignObjectIndex());
		dynamicsWorld->addRigidBody(body);
	}
	else
	{
		std::cout << body->getUserIndex() << std::endl;
	}
}

void PhysicsFacade::UpdateRigidBody(rigidBody* body)
{
	dynamicsWorld->getCollisionObjectArray()[body->getUserIndex()] = body;
}

//uses a heightmap to generate a collidable terrain
rigidBody* PhysicsFacade::CreateHeightFieldRigidBody(int heightStickWidth, int heightStickLength,
	const void * heightfieldData, float scaleWidth, float scaleHeight, float scaleLength,
	float heighestPoint, float lowestPoint)
{
	std::cout << "minimum height: " << lowestPoint << std::endl;
	std::cout << "maximum height: " << heighestPoint << std::endl;

	btScalar scaleX = (btScalar)scaleWidth;
	btScalar scaleY = (btScalar)scaleHeight;
	btScalar scaleZ = (btScalar)scaleLength;
	btScalar minH = (btScalar)lowestPoint;
	btScalar maxH = (btScalar)heighestPoint;
	btCollisionShape* hFieldShape = new btHeightfieldTerrainShape(heightStickWidth, heightStickLength,
		heightfieldData, scaleY, minH, maxH, 1, PHY_UCHAR, true);

	// scale the heightfield to match terrain mesh
	hFieldShape->setLocalScaling(btVector3(scaleX, 1.0, scaleZ));

	this->collisionShapes.push_back(hFieldShape);

	btTransform terrainTransform;
	terrainTransform.setIdentity();

	// translate heightfield to match terrain mesh
	terrainTransform.setOrigin(btVector3(((heightStickWidth * scaleX) / 2.f) - 1, (((heighestPoint + lowestPoint)) / 2.f) + 1, ((heightStickLength * scaleZ) / 2.f) - 1));

	btDefaultMotionState* hFieldMotionState = new btDefaultMotionState(terrainTransform);
	//has 0 mass, it's static, won't move.
	btRigidBody::btRigidBodyConstructionInfo hFieldRigidBodyCI(0, hFieldMotionState, hFieldShape, btVector3(0, 0, 0));
	btRigidBody* hFieldRigidBody = new btRigidBody(hFieldRigidBodyCI);

	if (heightfieldData)
	{
		std::cout << "HeightfieldData is not NULL" << std::endl;
	}

	terrainID = AssignObjectIndex();
	hFieldRigidBody->setUserIndex(terrainID);
	hFieldRigidBody->setFriction(btScalar(10));

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
	//std::cout << "hey boys" << std::endl;

	return sphereBody;
}

//doesn't appear to collide with terrain, will use capsules instead
rigidBody* PhysicsFacade::CreateBoxRigidBody(float h, float w, float l, float m, float xPos, float yPos, float zPos)
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
	//std::cout << "box made" << std::endl;

	return boxBody;
}

rigidBody* PhysicsFacade::CreatePlayerRigidBody(float radius, float height, float m, V3 pos, V3 iner)
{
	btCollisionShape* capsuleShape = new btCapsuleShape(radius, height);
	this->collisionShapes.push_back(capsuleShape);
	btTransform capsuleTransform;
	capsuleTransform.setIdentity();

	capsuleTransform.setOrigin(btVector3(pos.x, pos.y-7, pos.z));
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

rigidBody* PhysicsFacade::CreateCapsuleRigidBody(float radius, float height, float m, float xPos, float yPos, float zPos)
{
	btCollisionShape* capsuleShape = new btCapsuleShape(radius, height);
	this->collisionShapes.push_back(capsuleShape);
	btTransform capsuleTransform;
	capsuleTransform.setIdentity();

	capsuleTransform.setOrigin(btVector3(xPos, yPos, zPos));
	btScalar capsuleMass(m);

	bool isDynamic = (capsuleMass != 0.f);

	btVector3 localInertia(btVector3(0.f, 0.f, 0.f));

	if (isDynamic)
	{
		capsuleShape->calculateLocalInertia(capsuleMass, localInertia);
	}

	btDefaultMotionState* capsuleMotionState = new btDefaultMotionState(capsuleTransform);

	btRigidBody::btRigidBodyConstructionInfo capsuleRigidBodyCI(capsuleMass, capsuleMotionState, capsuleShape, localInertia);
	btRigidBody* capsuleRigidBody = new btRigidBody(capsuleRigidBodyCI);

	capsuleRigidBody->setUserIndex(AssignObjectIndex());

	//capsuleRigidBody->setGravity(btVector3(0, -10, 0));

	//dynamicsWorld->addRigidBody(capsuleRigidBody);

	return capsuleRigidBody;
}

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

		//if current body is the player's body
		if (body->getUserIndex() == playerID)
		{
			btVector3 playerP(btVector3(playerPos.x, playerPos.y, playerPos.z));
			playerForce.setX((playerP.getX() - playerPosition.getX()) * 100000);
			playerForce.setY((playerP.getY() - playerPosition.getY()) * 10000);
			playerForce.setZ((playerP.getZ() - playerPosition.getZ()) * 100000);

			body->applyCentralForce(playerForce);
			playerPosition = trans.getOrigin();
			
			//update parameter
			playerPos.x = float(trans.getOrigin().getX());
			playerPos.y = float(trans.getOrigin().getY());
			playerPos.z = float(trans.getOrigin().getZ());

			//std::cout << "world pos object " << i << " " << float(trans.getOrigin().getX()) << " "<< float(trans.getOrigin().getY()) << " " << float(trans.getOrigin().getZ()) << std::endl;
			playerPosition.setY(playerPosition.getY());
		}

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
		.addFunction("CreateCapsuleRigidBody", &PhysicsFacade::CreateCapsuleRigidBody)
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
