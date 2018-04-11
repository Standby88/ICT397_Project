#pragma once
#include "GameObject.h"
#include "Model.h"
class GameObject3D : public GameObject
{
protected:
	Model * objectModel;
	std::string objectType;
public:
	GameObject3D();
	virtual ~GameObject3D() {};
	virtual void Draw(Shader &S) = 0;
	std::string getObjectType();
	Model * getModel();
	void LoadModel(char * Path);

};

