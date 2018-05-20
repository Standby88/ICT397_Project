#include "GameObject3D.h"

void GameObject3D::UpdateSkeleton()
{
	skeleton.Update();
}

void GameObject3D::AddAnimation(Animation & in_anim)
{
	animations.push_back(in_anim);
	if (animations.size() > 0)
	{
		anim = true;
	}
}
Animation * GameObject3D::FindAnimation(std::string anim_to_find)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (animations.at(i).name == anim_to_find)
			return &animations.at(i);
	}
	return nullptr;
}

void GameObject3D::PlayAnimation(Animation & anim, bool loop, bool reset_to_start)
{
	skeleton.PlayAnimation(anim, loop, reset_to_start);
}
void GameObject3D::StopAnimating()
{
	skeleton.StopAnimating();
}
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
	if (objectModel->checkMeshSize() == true)
	{
		skeleton = objectModel->getFirstMesh().sceneLoaderSkeleton;
	}
	
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


