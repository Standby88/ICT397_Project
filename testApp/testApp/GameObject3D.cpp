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

void GameObject3D::LoadModel(char * Path)
{
}


