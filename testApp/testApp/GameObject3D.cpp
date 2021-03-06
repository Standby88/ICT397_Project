#include "GameObject3D.h"




GameObject3D::GameObject3D()
{
}

std::string GameObject3D::getObjectType()
{
	return objectType;
}

Model * GameObject3D::getModel()
{
	return objectModel;
}

void GameObject3D::addModel(Model * model)
{
	objectModel = model;
	//(objectModel->)
	
}

void GameObject3D::SetRigidBody(rigidBody* body)
{
	std::cout << "sphere body created" << std::endl;
	gameObjBody = body;
}

rigidBody* GameObject3D::GetRigidBody()
{
	return gameObjBody;
}

void GameObject3D::UpdateRigidBodyPosition(V3 position)
{
	gameObjBody->getWorldTransform().getOrigin().setX(btScalar(position.x));
	gameObjBody->getWorldTransform().getOrigin().setY(btScalar(position.y));
	gameObjBody->getWorldTransform().getOrigin().setZ(btScalar(position.z));
}

void GameObject3D::UpdateRigidBodyVelocity(V3 vel)
{
	gameObjBody->setLinearVelocity(btVector3(vel.x, vel.y, vel.z));
}

void GameObject3D::UpdatePhysicsWorldBody()
{
	gOPhys->UpdateRigidBody(this->gameObjBody);
}

void GameObject3D::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("GA")
		.deriveClass<GameObject3D,GameObject>("GameObject3D")
		//.addConstructor<void(*) (void)>()
		.addFunction("addModel", &GameObject3D::addModel)
		.addFunction("getModel", &GameObject3D::getModel)
		.addFunction("SetRigidBody", &GameObject3D::SetRigidBody)
		.addFunction("GetRigidBody", &GameObject3D::GetRigidBody)
		.addFunction("getObjectType", &GameObject3D::getObjectType)
		.endClass()
		.endNamespace();
}


