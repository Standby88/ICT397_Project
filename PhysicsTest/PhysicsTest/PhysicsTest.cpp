// PhysicsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "PhysicsFacade.h"

int main()
{
	std::cout << "Hello World!" << std::endl;

	PhysicsFacade pf = PhysicsFacade();
	
	pf.InitGravity();
	pf.CreateStaticRigidPlane(btVector3(0, 1, 0), 1);
	btCollisionShape* fallShape = new btSphereShape(1);
	pf.CreateFallingRigidBody(fallShape);
	for (int i = 0; i < 300; i++)
	{
		pf.StepSimulation(1 / 60.f, 10);
	}
	
	std::getchar();
	//pf.~PhysicsFacade();
	

    return 0;
}

