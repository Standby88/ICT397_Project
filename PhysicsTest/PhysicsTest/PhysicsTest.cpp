// PhysicsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "PhysicsFacade.h"
#include <fstream>

int main()
{
	std::cout << "Hello World!" << std::endl;

	//-------------------------------------------------------------
	char* filename = "height128.raw";
	unsigned char* terrainData = NULL; 
	int size = 128;
	//open for binary read
	std::ifstream infile(filename, std::ios::binary);
	if (!infile)
	{
		std::cerr << "Cannot open file: " << filename << std::endl;
		return false;
	}

	//allocate memory
	if (terrainData)
	{
		delete[] terrainData;
	}
	if (size > 0)
	{
		terrainData = new unsigned char[size*size];
	}
	if (terrainData == NULL)
	{
		return false;
	}

	//read in heightfield
	//get length of file
	infile.seekg(0, std::ios::end);
	int length = infile.tellg();

	//read data as a block
	infile.seekg(0, std::ios::beg);
	infile.read(reinterpret_cast<char*>(terrainData), length);
	infile.close();
	//-----------------------------------------------------------
	
	PhysicsFacade pf = PhysicsFacade();
	PhysicsVector grav(0, -10, 0);
	PhysicsVector planeNorm(1, 0, 0);
	PhysicsVector boxVec(1, 50, 0);
	float offSet = 2;

	//pf.InitPhysics(grav);
		//create a character
	//pf.CreateKinematicCharacter();
	pf.SetGravity(-10.f);
	pf.CreateHeightFieldRigidBody(10, 10, terrainData, 1, 1, false, false);
	pf.CreateSphereRigidBody(1, 1, 0, 50, 0, 0, 0, 0);
	//pf.CreateFallingBoxRigidBody(boxVec);
	for (int i = 0; i < 300; i++)
	{
		
		pf.StepSimulation(1 / 60.f, 10);
	}
	
	std::getchar();
	//pf.~PhysicsFacade();
	

    return 0;
}

