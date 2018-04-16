#include "PhysicsFacade.h"

PhysicsFacade::PhysicsFacade()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	
	overLappingPairCache = new btDbvtBroadphase();

	solver = new btSequentialImpulseConstraintSolver;
	
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overLappingPairCache, solver, collisionConfiguration);
	
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

void PhysicsFacade::SetGravity(float grav)
{
	dynamicsWorld->setGravity(btVector3(0, grav, 0));
}

/*void PhysicsFacade::InitPhysics(PhysicsVector& grav)
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
		//sets gravity
	btVector3 gravity = btVector3(grav.x, grav.y, grav.z);
	this->dynamicsWorld->setGravity(gravity);
}*/

/*int PhysicsFacade::AssignObjectIndex()
{
	return this->bodyIndex++;
}*/

/*void PhysicsFacade::CharacterSetup(float charW, float charH, float xPos, float yPos, float zPos, float m)
{
	this->pShape = new btCapsuleShape(charW, charH);
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(xPos, yPos, zPos));
	btDefaultMotionState* pMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo cInfo(m, pMotionState, pShape);
	this->pBody = new btRigidBody(cInfo);
	// kinematic vs. static doesn't work
	//m_rigidBody->setCollisionFlags( m_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	pBody->setSleepingThresholds(0.0, 0.0);
	pBody->setAngularFactor(0.0);
}*/

/*int PhysicsFacade::CreateKinematicCharacter()
{
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(0.0, 0.0, 0.0));
	btPairCachingGhostObject* ghostObject = new btPairCachingGhostObject();
	ghostObject->setWorldTransform(startTransform);
	btVector3 worldMin(-100, -100, -100);
	btVector3 worldMax(100, 100, 100);
	btAxisSweep3* sweepBP = new btAxisSweep3(worldMin, worldMax);
	sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	btScalar characterHeight = 1.75;
	btScalar characterWidth = 1.75;
	btConvexShape* capsule = new btCapsuleShape(characterWidth, characterHeight);
	ghostObject->setCollisionShape(capsule);
	ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

	btScalar stepHeight = btScalar(0.35);
	playerCharacter = new btKinematicCharacterController(ghostObject, capsule, stepHeight);
		//only collide with static for now (no interaction with dynamis objects)
	dynamicsWorld->addCollisionObject(ghostObject, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
	dynamicsWorld->addAction(playerCharacter);
	
	return AssignObjectIndex();
}*/


//uses a heightmap to generate a collidable terrain
void PhysicsFacade::CreateHeightFieldRigidBody(int 	heightStickWidth, int heightStickLength,
	const void * heightfieldData, float scaleHeight, int upAxis,
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
	std::cout << "Capacity of dynamicsWorld: " << dynamicsWorld->getCollisionObjectArray().capacity() << std::endl;
	dynamicsWorld->addRigidBody(hFieldRigidBody);
	std::cout << "Capacity of dynamicsWorld: " << dynamicsWorld->getCollisionObjectArray().capacity() << std::endl;
	
}

void PhysicsFacade::CreateSphereRigidBody(float rad, float m, float xPos, float yPos, float zPos, float xIner, float yIner, float zIner)
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
	btRigidBody* body = new btRigidBody(sphereRBCI);
	
	dynamicsWorld->addRigidBody(body);

	
}

void PhysicsFacade::CreateRigidBodyBox(int h, int w, int l, int m, int xPos, int yPos, int zPos, int xIner, int yIner, int zIner)
{
	btCollisionShape* boxShape = new btBoxShape(btVector3(btScalar(w), btScalar(h), btScalar(l)));
	this->collisionShapes.push_back(boxShape);
	btTransform boxTransform;
	boxTransform.setIdentity();

	boxTransform.setOrigin(btVector3(xPos, yPos, zPos));
	btScalar boxMass = m;

	bool isDynamic = (boxMass != 0.f);

	btVector3 localInertia(xIner, yIner, zIner);

	if (isDynamic)
	{
		boxShape->calculateLocalInertia(boxMass, localInertia);
	}

	btDefaultMotionState* boxMotionState = new btDefaultMotionState(boxTransform);
	
	btRigidBody::btRigidBodyConstructionInfo groundRBCI(boxMass, boxMotionState, boxShape, localInertia);
	btRigidBody* body = new btRigidBody(groundRBCI);
	
	dynamicsWorld->addRigidBody(body);
	
	
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

void PhysicsFacade::CharacterMovement(int charIndex, float dt, int moveDir)
{
	//set walk direction for our character
	btTransform walkDir;
	walkDir = dynamicsWorld->getCollisionObjectArray().at(charIndex)->getWorldTransform();

	btVector3 forwardDir = walkDir.getBasis()[2];
	btVector3 upDir = walkDir.getBasis()[1];
	btVector3 strafeDir = walkDir.getBasis()[0];
	forwardDir.normalize();
	upDir.normalize();
	strafeDir.normalize();

	btVector3 walkDirection = btVector3(0.0, 0.0, 0.0);
	btScalar walkVelocity = btScalar(1.1) * 4.0; // 4km/h -> 1.1m/s
	//not sure what dt should be right now, it's supposed to be the time interval between calculations, i.e the frame rate I believe
	btScalar walkSpeed = walkVelocity * (dt/1000.0f);
	
	/* Camera will rotate view, no need to do it here
	if (gLeft)	//not sure what "gleft" should be right now
	{
		btMatrix3x3 orn = dynamicsWorld->getCollisionObjectArray().at(charIndex)->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0, 1, 0), 0.01));
		dynamicsWorld->getCollisionObjectArray().at(charIndex)->getWorldTransform().setBasis(orn);
	}

	if (gRight)
	{
		btMatrix3x3 orn = dynamicsWorld->getCollisionObjectArray().at(charIndex)->getWorldTransform().getBasis();
		orn *= btMatrix3x3(btQuaternion(btVector3(0, 1, 0), -0.01));
		dynamicsWorld->getCollisionObjectArray().at(charIndex)->getWorldTransform().setBasis(orn);
	}*/

	if (moveDir == 1)
	{
		walkDirection += forwardDir;
	}

	if (moveDir == 2)
	{
		walkDirection -= forwardDir;
	}

}

void PhysicsFacade::StepSimulation(float tStep, int maxSubSteps)
{
	dynamicsWorld->stepSimulation(tStep, maxSubSteps);
		//print positions of all objects
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			trans = obj->getWorldTransform();
		}
		std::cout << "world pos object " << i << " " << float(trans.getOrigin().getX()) << " "
			<< float(trans.getOrigin().getY()) << " " << float(trans.getOrigin().getZ()) << std::endl;
	}
	
}

float PhysicsFacade::GetXOrigin(int i)
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

float PhysicsFacade::GetYOrigin(int i)
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

float PhysicsFacade::GetZOrigin(int i)
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

/*void PhysicsFacade::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.beginClass<GameObject>("GameObject")
		.addConstructor<void(*) (void)>()
		.addFunction("updateObject", &GameObject::updateOject)
		.addFunction("getObjectPos", &GameObject::getObjectPos)
		.endClass()
		.endNamespace();
}*/

